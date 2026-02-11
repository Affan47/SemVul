UINTToByte(uint8_t* Output, const uint32_t* Input, uint32_t nLength,
                     int& error)
{

        if( nLength % 4 != 0 ) error = -22;

        uint32_t i = 0;
        uint32_t j = 0;
        for ( ; j < nLength; i++, j += 4)
        {
                Output[j] =   (uint8_t)(Input[i] & 0xff);
                Output[j+1] = (uint8_t)((Input[i] >> 8) & 0xff);
                Output[j+2] = (uint8_t)((Input[i] >> 16) & 0xff);
                Output[j+3] = (uint8_t)((Input[i] >> 24) & 0xff);
        }
}
