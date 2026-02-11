Read(FilePath filename, FilePath directoryForImports,
                       FilePath imports[], int sizeImports) {
	FILE *rcfile = filename.Open(fileRead);
	if (rcfile) {
		unsigned int lenFile;
		char *propsData;

		fseek (rcfile, 0, SEEK_END);
		lenFile = ftell (rcfile);
		fseek (rcfile, 0, SEEK_SET);
		propsData = new char[lenFile];
		lenFile = fread(propsData, 1, lenFile, rcfile);
		fclose(rcfile);
		const char *data = propsData;
		if (memcmp(data, "\xef\xbb\xbf", 3) == 0) {
			data += 3;
			lenFile -= 3;
		}
		ReadFromMemory(data, lenFile, directoryForImports, imports, sizeImports);
		return true;
	}
	return false;
}
