rescale_byte_wise2x2(	int 				bytecount,
                                                                                                                                        const byte 	*inbytea,
                                                                                                                                        const byte 	*inbyteb,
                                                                                                                                        byte 				*outbyte)
{
        register int i, j;
        int max = bytecount / 2;

        for (i = 0; i < max; i += 4) {
                j = 2 * i;

                outbyte[i + 1] = (inbytea[j + 1] + inbytea[j + 5] + inbyteb[j + 1] + inbyteb[j + 5]) / 4;


                outbyte[i + 2] = (inbytea[j + 2] + inbytea[j + 6] + inbyteb[j + 2] + inbyteb[j + 6]) / 4;


                outbyte[i + 3] = (inbytea[j + 3] + inbytea[j + 7] + inbyteb[j + 3] + inbyteb[j + 7]) / 4;
        }

        return (max);
}
