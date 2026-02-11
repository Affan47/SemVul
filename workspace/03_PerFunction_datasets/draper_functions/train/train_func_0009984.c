AiffCloseFile(AiffInfo *ai)
{
    int             status = 0;

    if (ai->fp)
    {
	if (ai->writing)
	{
	    if (ai->dataSize & 1)
		fputc(0, ai->fp);

	    fseek(ai->fp, ai->sizeOffset, 0);
	    FileWriteL(ai->fileSize + PAD2(ai->dataSize), ai->fp,
		       NAS_LITTLE_ENDIAN);
	    fseek(ai->fp, ai->dataOffset, 0);
	    FileWriteL(ai->dataSize, ai->fp, NAS_LITTLE_ENDIAN);
	}

	status = fclose(ai->fp);
    }

    if (ai->comment)
	free(ai->comment);

    free(ai);
    return status;
}
