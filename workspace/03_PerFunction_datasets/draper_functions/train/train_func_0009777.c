digestControlFile(ControlFileData *ControlFile, char *src, size_t size)
{
	if (size != PG_CONTROL_SIZE)
		pg_fatal("unexpected control file size %d, expected %d\n",
				 (int) size, PG_CONTROL_SIZE);

	memcpy(ControlFile, src, sizeof(ControlFileData));


	checkControlFile(ControlFile);
}
