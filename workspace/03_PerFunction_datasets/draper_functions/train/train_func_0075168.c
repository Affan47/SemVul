Filter(Data &dest, const Data &src, unsigned int destoffset)
{
	const unsigned char *b = src.GetData(), *e = src.GetData() + src.GetSize();
	size_t needed = src.GetSize() / 2 * 3 + 4 + destoffset;
	unsigned char *buf = dest.GetBuffer(needed) + destoffset;
	unsigned char *put = buf;

	while( b != e ) {


		if( m_last == 0x7e ) {
			m_last = 0;
			if( *b != 0x7e )
				*put++ = 0x7e;
			else
				*put++ = *b++;
		}


		while( b != e && *b != 0x7e ) {
			*put++ = *b++;
		}

		if( b != e ) {
			*put++ = *b++;
			m_last = 0x7e;
		}
	}

	dest.ReleaseBuffer(put - buf + destoffset);
}
