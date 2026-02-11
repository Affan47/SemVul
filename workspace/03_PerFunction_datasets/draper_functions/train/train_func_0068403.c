checksum(const char *filename)
	{
		Uint32 cs = 0;
		SDL_RWops *stream = open(filename);
		if (stream)
		{
			int length = SDL_RWseek(stream, 0, SEEK_END);
			SDL_RWseek(stream, 0, SEEK_SET);

			int lengthBlock = length & (~0x3);
			for (int i=0; i<(lengthBlock>>2); i++)
			{
				cs ^= SDL_ReadBE32(stream);
				cs = (cs<<31)|(cs>>1);
			}
			int lengthRest = length & 0x3;
			for (int i=0; i<lengthRest; i++)
			{
				unsigned char c;
				SDL_RWread(stream, &c, 1, 1);
				cs ^= (static_cast<Uint32>(c))<<(8*i);
			}
			SDL_RWclose(stream);
		}
		return cs;
	}
