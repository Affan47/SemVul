create_wep_packet(unsigned char* packet, int *length, int data_begin)
{
    if(packet == NULL) return 1;


    if( add_crc32(packet + data_begin, *length - data_begin) != 0 )               return 1;


    if( encrypt_data(packet + data_begin + 4, packet + data_begin, *length-(data_begin - 4)) != 0 ) return 1;


    if( set_IVidx(packet, data_begin) != 0 )                              return 1;


    packet[1] = packet[1] | 0x40;

    *length+=8;


    return 0;
}
