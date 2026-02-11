iSizeSeek(ILint Offset, ILuint Mode)
{
	switch (Mode)
	{
		case IL_SEEK_SET:
			CurPos = Offset;
			if (CurPos > MaxPos)
				MaxPos = CurPos;
			break;

		case IL_SEEK_CUR:
			CurPos = CurPos + Offset;
			break;

		case IL_SEEK_END:
			CurPos = MaxPos + Offset;
			break;

		default:
			ilSetError(IL_INTERNAL_ERROR);
			return -1;
	}

	if (CurPos > MaxPos)
		MaxPos = CurPos;

	return 0;
}
