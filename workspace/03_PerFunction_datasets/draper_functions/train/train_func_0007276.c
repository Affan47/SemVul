oki_transpose(byte *in, byte *out, int scanBits, register int lineSize)
{
        register int bitMask = 0x80;
        register byte *inPtr;
        register byte outByte;

        while (scanBits-- > 0) {

                inPtr = in;

                if (*inPtr & bitMask)
                        outByte = 0x81;
                else
                        outByte = 0x80;
                if (*(inPtr += lineSize) & bitMask)
                        outByte += 0x02;
                if (*(inPtr += lineSize) & bitMask)
                        outByte += 0x04;
                if (*(inPtr += lineSize) & bitMask)
                        outByte += 0x08;
                if (*(inPtr += lineSize) & bitMask)
                        outByte += 0x10;
                if (*(inPtr += lineSize) & bitMask)
                        outByte += 0x20;
                if (*(inPtr += lineSize) & bitMask)
                        outByte += 0x40;

                *out++ = outByte;

                if ((bitMask >>= 1) == 0) {
                        bitMask = 0x80;
                        in ++;
                }
        }
}
