skip_ps_header(FILE * PSfile)
{
	char            S[256];
	int             header_lines;


	if (NULL == fgets(S, 256, PSfile))
		gr_Error("PostScript file is empty");
	if (feof(PSfile))
		gr_Error("PostScript file is empty");
	if (!strcmp(S, "%!\n")) {
		if (NULL == fgets(S, 256, PSfile))
			gr_Error("PostScript file is nearly empty");
		if (feof(PSfile))
			gr_Error("PostScript file is nearly empty");
		if (1 == sscanf(&S[1], "%d header lines follow\n",
				&header_lines)) {
			while (header_lines-- > 0) {
				if (NULL == fgets(S, 256, PSfile))
					gr_Error("badly formed (old-style) header");
				if (feof(PSfile))
					gr_Error("badly formed (old-style) header");
			}
		} else {
			gr_Error("badly formed (old-style) header");
		}
	} else if (!strcmp(S, "%!PS-Adobe-1.0\n"))
		while (strncmp(S, "%%Page:", 7)) {
			if (NULL == fgets(S, 256, PSfile))
				gr_Error("badly formed header");
			if (feof(PSfile))
				gr_Error("badly formed header");
		}
}
