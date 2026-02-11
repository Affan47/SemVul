intercept(uchar* packet, int length)
{
    uchar buf[4096];
    uchar K[128];
    int z=0;

    memset(buf, 0, 4096);

    z = ( ( packet[1] & 3 ) != 3 ) ? 24 : 30;

    if( opt.crypt == CRYPT_WEP )
    {
        memcpy( K, packet + z, 3 );
        memcpy( K + 3, opt.wepkey, opt.weplen );

        if (decrypt_wep( packet + z + 4, length - z - 4,
                        K, 3 + opt.weplen ) == 0 )
        {

            return 1;
        }


        length -= 8;

        memcpy( packet + z, packet + z + 4, length - z );
    }


    packet[1] &= 0xBF;


    memcpy(buf+14, packet, length);
    length += 14;

    ti_write(dev.dv_ti2, buf, length);
    return 0;
}
