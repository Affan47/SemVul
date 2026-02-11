decode_spchar_number( const char* in_char, const int offset, const int lng )
{
    char str_num[ 16 ];

    memcpy( str_num, in_char + offset, lng );
    str_num[ lng ] = '\0';

#ifdef _DEBUG
    std::cout << "MISC::decode_spchar_number offset = " << offset << " lng = " << lng << " str = " << str_num << std::endl;
#endif

    int num = 0;
    if( offset == 2 ) num = atoi( str_num );
    else num = strtol( str_num, NULL, 16 );

    return num;
}
