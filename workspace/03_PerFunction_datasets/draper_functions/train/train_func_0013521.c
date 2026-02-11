gifti_write_image(gifti_image *gim, const char *fname, int write_data)
{
    int errs = 0;

    if( !gim ) {
        fprintf(stderr,"** gifti_write_image, missing gifti_image\n");
        errs++;
    } else if( !fname ) {
        fprintf(stderr,"** gifti_write_image: missing filename\n");
        errs++;
    }

    if( errs ) return 1;

    gxml_set_verb(G.verb);

    return gxml_write_image(gim, fname, write_data);
}
