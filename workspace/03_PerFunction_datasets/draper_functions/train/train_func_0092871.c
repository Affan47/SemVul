USPS_MSB_Math_CRC11GenerateFrameCheckSequence( unsigned char *ByteArrayPtr )
{
        unsigned short  GeneratorPolynomial = 0x0F35;
        unsigned short  FrameCheckSequence  = 0x07FF;
        unsigned short  Data;
        int             ByteIndex, Bit;


        Data = *ByteArrayPtr << 5;
        ByteArrayPtr++;
        for ( Bit = 2; Bit < 8; Bit++ )
        {
                if ( (FrameCheckSequence ^ Data) & 0x400 )
                {
                        FrameCheckSequence = (FrameCheckSequence << 1) ^ GeneratorPolynomial;
                }
                else
                {
                        FrameCheckSequence = (FrameCheckSequence << 1);
                }
                FrameCheckSequence &= 0x7FF;
                Data <<= 1;
        }


        for ( ByteIndex = 1; ByteIndex < 13; ByteIndex++ )
        {
                Data = *ByteArrayPtr << 3;
                ByteArrayPtr++;
                for ( Bit = 0; Bit < 8; Bit++ )
                {
                        if ( (FrameCheckSequence ^ Data) & 0x0400 )
                        {
                                FrameCheckSequence = (FrameCheckSequence << 1) ^ GeneratorPolynomial;
                        }
                        else
                        {
                                FrameCheckSequence = (FrameCheckSequence << 1);
                        }
                        FrameCheckSequence &= 0x7FF;
                        Data <<= 1;
                }
        }

        return FrameCheckSequence;
}
