create(int size, int blockSize)
{
	filename = getFilename();


	if (size < (sizeof(struct SUPERBLOCK) + sizeof(struct INODE) + 10 * blockSize))
	{
		printf("Rozmiar partycji jest nieprawidlowy\n");
		return 1;
	}

	partitionFile = fopen(filename, "wb");

	format(size, blockSize);

	fclose(partitionFile);

	free(filename);

	return 0;
}
