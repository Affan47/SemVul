BufList()
{
	register const char	*fmt = "%2s %5s %-8s %-1s%-1s %-*s  %-s";
	register Buffer	*b;
	int	bcount = 1,
		buf_width = 11;
	bool
		any_needsaving = NO,
		any_tempmodified = NO,
		any_ntbf = NO,
		any_diverged = NO;

	for (b = world; b != NULL; b = b->b_next) {
		buf_width = max(buf_width, (int)strlen(b->b_name));
		if (b->b_type == B_FILE)
		    any_needsaving |= IsModified(b);
		else
		    any_tempmodified |= IsModified(b);
		any_ntbf |= b->b_ntbf;
		any_diverged |= b->b_diverged;
	}

	TOstart("Buffer list");

	if (any_needsaving)
		Typeout("(* means buffer needs saving)");
	if (any_tempmodified)
		Typeout("(+ means temporary buffer has been modified)");
	if (any_ntbf)
		Typeout("(- means file hasn't been read yet)");
	if (any_diverged)
		Typeout("(# means file has been changed since buffer was read or written)");
	if (any_needsaving | any_tempmodified | any_ntbf | any_diverged)
		Typeout(NullStr);
	Typeout(fmt, "NO", "Lines", "Type", NullStr, NullStr, buf_width, "Name", "File");
	Typeout(fmt, "--", "-----", "----", NullStr, NullStr, buf_width, "----", "----");
	for (b = world; b != NULL; b = b->b_next) {
		char
			bnostr[10],
			linestr[10];

		swritef(bnostr, sizeof(bnostr), "%d", bcount++);
		if (b->b_ntbf)
			strcpy(linestr, "?");
		else
			swritef(linestr, sizeof(linestr), "%d",
				LinesTo(b->b_first, (LinePtr)NULL));
		Typeout(fmt, bnostr, linestr, TypeNames[b->b_type],
				b->b_diverged ? "#" : NullStr,
				IsModified(b)
				    ? (b->b_type==B_FILE? "*" : "+")
				    : b->b_ntbf ? "-" : NullStr,
				buf_width,
				b->b_name,
				filename(b));

		if (TOabort)
			break;
	}
	TOstop();
}
