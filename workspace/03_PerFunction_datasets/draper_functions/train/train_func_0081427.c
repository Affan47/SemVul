groupInfos( const ByteArray& text )
	{
		int offset = 10;
		std::list< GroupInfo > list;
		while( offset < text.size() )
		{
			list.push_back(
				GroupInfo( ntohl( type_cast<int>( text.data()+offset ) ),
				type_cast<char>(text.data()+offset+4), ( type_cast<short>(text.data()+5) >> 2) & 0x3f ) );
			offset += 6;
		}
		return list;
	}
