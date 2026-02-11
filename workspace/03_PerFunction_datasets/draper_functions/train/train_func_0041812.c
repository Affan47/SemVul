set_hdr_flag( headeredness new_flag)
{
    headeredness new_state = new_flag;
    switch ( new_flag)
    {
	case FLAG_HEADERLESS:
	    {
		if ( always_headers )
		{   new_state = FLAG_HEADERS;
		}

	    }
	case FLAG_HEADERS:
	    {
		if ( always_external )
		{   new_state = FLAG_EXTERNAL;
		}

	    }
	case FLAG_EXTERNAL:
	    break;

    }

    hdr_flag = new_state;

}
