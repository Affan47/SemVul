hashFromNumberString(const string& number)
{
    const char* str = number.c_str();
    const short upperBound = number.length()<(maxLen+1)?number.length():maxLen+1;

    uint32_t hash(0);

    for( int i = 0; i < upperBound; ++i)
    {
        char c = str[i];
        if( c >= '2' && c <= '9' )
        {
            c -= '2';
        }
        else
        {
            return invalidHash;
        }

        hash |= c << (i*3);

    }
    hash |= (upperBound << 27);


    return hash;

}
