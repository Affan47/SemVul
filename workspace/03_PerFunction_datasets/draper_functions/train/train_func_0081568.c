xntohl(unsigned int x)
{
    if ( *((char *)&xendian) == 0x01 )
        return(x);
    else
        return( ((x & 0x000000ffU) << 24) |
                ((x & 0x0000ff00U) <<  8) |
                ((x & 0x00ff0000U) >>  8) |
                ((x & 0xff000000U) >> 24) );
}
