XpmGetsInternal(ILubyte *Buffer, ILint MaxLen)
{
	ILint	i = 0, Current;

	if (ieof())
		return IL_EOF;

	while ((Current = igetc()) != IL_EOF && i < MaxLen - 1) {
		if (Current == IL_EOF)
			return 0;
		if (Current == '\n')
			break;

		if (Current == '\r') {
			Current = igetc();
			if (Current == '\n')
				break;

			if (Current == IL_EOF)
				break;

			Buffer[i++] = (ILubyte)Current;
			continue;
		}
		Buffer[i++] = (ILubyte)Current;
	}

	Buffer[i++] = 0;

	return i;
}
