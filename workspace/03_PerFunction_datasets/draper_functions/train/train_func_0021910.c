dbcs_ptr2cells(p)
    char_u	*p;
{


    if (enc_dbcs == DBCS_JPNU && *p == 0x8e)
	return 1;
    return MB_BYTE2LEN(*p);
}
