LogLuvDecode24(TIFF* tif, tidata_t op, tsize_t occ, tsample_t s)
{
        LogLuvState* sp = DecoderState(tif);
        int cc, i, npixels;
        unsigned char* bp;
        uint32* tp;

        assert(s == 0); (void)s;
        assert(sp != NULL);

        npixels = occ / sp->pixel_size;

        if (sp->user_datafmt == SGILOGDATAFMT_RAW)
                tp = (uint32 *)op;
        else {
                assert(sp->tbuflen >= npixels);
                tp = (uint32 *) sp->tbuf;
        }

        bp = (unsigned char*) tif->tif_rawcp;
        cc = tif->tif_rawcc;
        for (i = 0; i < npixels && cc > 0; i++) {
                tp[i] = bp[0] << 16 | bp[1] << 8 | bp[2];
                bp += 3;
                cc -= 3;
        }
        tif->tif_rawcp = (tidata_t) bp;
        tif->tif_rawcc = cc;
        if (i != npixels) {
                TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
            "LogLuvDecode24: Not enough data at row %d (short %d pixels)",
                    tif->tif_row, npixels - i);
                return (0);
        }
        (*sp->tfunc)(sp, op, npixels);
        return (1);
}
