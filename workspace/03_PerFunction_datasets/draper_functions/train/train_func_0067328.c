GetCRC32Table( wxUint32 *crc_table )
{

    if ( !crc_table )
    {

        crc_table = new wxUint32[256];


        if ( crc_table )
        {

            for(unsigned int i = 0; i < 256; ++i)
            {
                wxUint32 crc = i;
                for (unsigned int j = 8; j > 0; --j)
                {
                    if (crc & 1) crc = (crc >> 1) ^ 0xEDB88320UL;
                    else         crc >>= 1;
                }
                crc_table[i] = crc;
            }
        }
    }


    return ( crc_table ) ;
}
