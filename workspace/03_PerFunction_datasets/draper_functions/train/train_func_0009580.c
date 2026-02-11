ZIPPostEncode(TIFF* tif)
{
        ZIPState *sp = EncoderState(tif);
        static const char module[] = "ZIPPostEncode";
        int state;

        sp->stream.avail_in = 0;
        do {
                state = deflate(&sp->stream, Z_FINISH);
                switch (state) {
                case Z_STREAM_END:
                case Z_OK:
                    if ((int)sp->stream.avail_out != (int)tif->tif_rawdatasize)
                    {
                            tif->tif_rawcc =
                                tif->tif_rawdatasize - sp->stream.avail_out;
                            TIFFFlushData1(tif);
                            sp->stream.next_out = tif->tif_rawdata;
                            sp->stream.avail_out = tif->tif_rawdatasize;
                    }
                    break;
                default:
                        TIFFErrorExt(tif->tif_clientdata, module, "%s: zlib error: %s",
                        tif->tif_name, sp->stream.msg);
                    return (0);
                }
        } while (state != Z_STREAM_END);
        return (1);
}
