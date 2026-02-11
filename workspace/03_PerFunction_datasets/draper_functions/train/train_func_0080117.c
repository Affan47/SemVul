isHeaderValid(const SNPKHeader& header)
	{
		const c8* const tag = header.Tag;
		return tag[0] == '0' &&
			   tag[1] == 'K' &&
			   tag[2] == 'P' &&
			   tag[3] == 'N';
	}
