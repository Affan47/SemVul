gxml_write_image(gifti_image * gim, const char * fname, int write_data)
{
    gxml_data * xd = &GXD;
    FILE      * fp;

    if( !gim ) {
        fprintf(stderr,"** GXML write: no gifti_image\n");
        return 1;
    } else if ( !fname ) {
        fprintf(stderr,"** GXML write: no filename\n");
        return 1;
    }

    if(GXD.verb > 1) {
        fprintf(stderr,"++ writing gifti image (%s data) to '%s'",
                write_data?"with":"no", fname);
        if( write_data )
            fprintf(stderr," (%d DA elements = %lld MB)",
                    gim->numDA, gifti_gim_DA_size(gim,1));
        fputc('\n', stderr);
    }

#ifndef HAVE_ZLIB
    if( gim->darray && gim->darray[0] &&
                       gim->darray[0]->encoding == GIFTI_ENCODING_B64GZ ) {
        fprintf(stderr,"** no ZLIB for compression...\n");
        gifti_set_atr_in_DAs(gim, "Encoding", "Base64Binary", NULL, 0);
    }
#endif

    init_gxml_data(xd, 0, NULL, 0);
    xd->dstore = write_data;
    xd->gim = gim;


    if( xd->update_ok ) {
        if( xd->verb > 2 )
            fprintf(stderr,"++ setting GIFTI MD: gifticlib-version to %s\n",
                    gifticlib_version());
        gifti_add_to_meta(&gim->meta,"gifticlib-version",gifticlib_version(),1);
    }

    fp = fopen(fname, "w");
    if( !fp ) {
        fprintf(stderr,"** failed to open '%s' for gifti write\n", fname);
        return 1;
    }

    (void)gxml_write_gifti(xd, fp);

    if( xd->xdata ){ free(xd->xdata);  xd->xdata = NULL; }
    if( xd->zdata) { free(xd->zdata);  xd->zdata = NULL; }

    fclose(fp);

    return 0;
}
