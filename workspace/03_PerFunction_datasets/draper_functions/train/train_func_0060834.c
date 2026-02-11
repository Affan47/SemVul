get_text_address( char * text, ubyte * address )
{

	in_addr temp_addr;

	switch ( Multi_options_g.protocol ) {
		case NET_IPX:
			strcpy( text, XSTR("[ipx address here]",903) );
			sprintf(text, "%x %x %x %x %x %x",	address[0],
															address[1],
															address[2],
															address[3],
															address[4],
															address[5]);

			break;

		case NET_TCP:
			memcpy(&temp_addr.s_addr, address, 4);
			strcpy( text, inet_ntoa(temp_addr) );
			break;

		default:
			Assert(0);
			break;

	}

	return text;
}
