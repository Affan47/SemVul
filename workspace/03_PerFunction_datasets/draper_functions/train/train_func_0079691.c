openCompressedInputStreamBackend(const char *filename)
	{
		for (size_t i = 0; i < dirList.size(); ++i)
		{
			std::string path(dirList[i]);
			path += DIR_SEPARATOR;
			path += filename;

			FILE *fp = fopen(path.c_str(), "rb");
			if(fp)
			{
				fclose(fp);
				return new ZLibStreamBackend(path, true);
			}
		}

		return new ZLibStreamBackend("", false);
	}
