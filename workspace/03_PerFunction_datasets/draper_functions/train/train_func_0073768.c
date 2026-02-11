LZWPreDecode(TIFF* tif, tsample_t s)
{
        LZWCodecState *sp = DecoderState(tif);

        (void) s;
        assert(sp != NULL);


        if (tif->tif_rawdata[0] == 0 && (tif->tif_rawdata[1] & 0x1)) {
#ifdef LZW_COMPAT
                if (!sp->dec_decode) {
                        TIFFWarningExt(tif->tif_clientdata, tif->tif_name,
                            "Old-style LZW codes, convert file");


                        tif->tif_decoderow = LZWDecodeCompat;
                        tif->tif_decodestrip = LZWDecodeCompat;
                        tif->tif_decodetile = LZWDecodeCompat;


                        (*tif->tif_setupdecode)(tif);
                        sp->dec_decode = LZWDecodeCompat;
                }
                sp->lzw_maxcode = MAXCODE(BITS_MIN);
#else
                if (!sp->dec_decode) {
                        TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
                            "Old-style LZW codes not supported");
                        sp->dec_decode = LZWDecode;
                }
                return (0);
#endif
        } else {
                sp->lzw_maxcode = MAXCODE(BITS_MIN)-1;
                sp->dec_decode = LZWDecode;
        }
        sp->lzw_nbits = BITS_MIN;
        sp->lzw_nextbits = 0;
        sp->lzw_nextdata = 0;

        sp->dec_restart = 0;
        sp->dec_nbitsmask = MAXCODE(BITS_MIN);
#ifdef LZW_CHECKEOS
        sp->dec_bitsleft = tif->tif_rawcc << 3;
#endif
        sp->dec_free_entp = sp->dec_codetab + CODE_FIRST;


        _TIFFmemset(sp->dec_free_entp, 0, (CSIZE-CODE_FIRST)*sizeof (code_t));
        sp->dec_oldcodep = &sp->dec_codetab[-1];
        sp->dec_maxcodep = &sp->dec_codetab[sp->dec_nbitsmask-1];
        return (1);
}
