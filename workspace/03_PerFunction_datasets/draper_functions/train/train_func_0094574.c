populateFileList()
{
	STarHeader fHead;
	Files.clear();

	u32 pos = 0;
	while ( s32(pos + sizeof(STarHeader)) < File->getSize())
	{

		File->seek(pos);


		File->read(&fHead, sizeof(fHead));


		if (fHead.Link == ETLI_REGULAR_FILE || ETLI_REGULAR_FILE_OLD)
		{
			io::path fullPath = "";
			fullPath.reserve(255);


			if (!strncmp(fHead.Magic, "ustar", 5))
			{
				c8* np = fHead.FileNamePrefix;
				while(*np && (np - fHead.FileNamePrefix) < 155)
					fullPath.append(*np);
				np++;
			}


			c8* np = fHead.FileName;
			while(*np && (np - fHead.FileName) < 100)
			{
				fullPath.append(*np);
				np++;
			}


			core::stringc sSize = "";
			sSize.reserve(12);
			np = fHead.Size;
			while(*np && (np - fHead.Size) < 12)
			{
				sSize.append(*np);
				np++;
			}

			u32 size = strtoul(sSize.c_str(), NULL, 8);
#if !defined(_IRR_WINDOWS_CE_PLATFORM_)
			if (errno == ERANGE)
				os::Printer::log("File too large", fullPath, ELL_WARNING);
#endif


			u32 offset = pos + 512;


			pos = offset + (size / 512) * 512 + ((size % 512) ? 512 : 0);


			addItem(fullPath, size, false, Offsets.size());
			Offsets.push_back(offset);
		}
		else
		{


			pos += 512;
		}

	}

	return Files.size();
}
