write_appledouble(GFile *f, LPCTSTR pictname)
{
    unsigned char data[256];
    unsigned long resource_length;


    resource_length = write_resource_pict(NULL, pictname);

    memset(data, 0, sizeof(data));
    memcpy(data, apple_double_magic, 4);
    put_bigendian_dword(data+4, 0x00020000);

    put_bigendian_word(data+24, 2);

    put_bigendian_dword(data+26, 9);
    put_bigendian_dword(data+30, 50);
    put_bigendian_dword(data+34, 32);

    put_bigendian_dword(data+38, 2);
    put_bigendian_dword(data+42, 82);
    put_bigendian_dword(data+46, resource_length);

    memcpy(data+50, "EPSF", 4);
    memcpy(data+54, "MSWD", 4);
    data[58] = 1;
    gfile_write(f, data, 82);


    if (write_resource_pict(f, pictname) <= 0)
	return -1;
    return 0;
}
