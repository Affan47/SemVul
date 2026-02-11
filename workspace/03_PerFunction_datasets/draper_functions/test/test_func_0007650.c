file_size(fh)
    int fh;
{
    int siz;
#endif
    zoff_t ofs;
    char waste[4];

#ifdef USE_STRM_INPUT

    sts = zfseeko(file, 0, SEEK_END);
    if (sts != 0) {

        ofs = EOF;
    } else {

        ofs = zftello(file);
        if (ofs < 0) {

            ofs = EOF;
        } else {


            sts = zfseeko(file, ofs, SEEK_SET);
            if (sts != 0) {

                ofs = EOF;
            } else {

                siz = fread(waste, 1, 1, file);
                if (feof(file) == 0) {

                    ofs = EOF;
                }
            }
        }
    }
#else

    ofs = zlseek(fh, 0, SEEK_END);
    if (ofs == (zoff_t) -1) {

        ofs = EOF;
    } else if (ofs < 0) {

        ofs = EOF;
    } else {


        ofs = zlseek(fh, ofs, SEEK_SET);
        if (ofs == (zoff_t) -1) {

            ofs = EOF;
        } else {

            siz = read(fh, waste, 1);
            if (siz != 0) {

                ofs = EOF;
            }
        }
    }
#endif
    return ofs;
}
