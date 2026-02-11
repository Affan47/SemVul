make_iso_poly_3
          ( int *conn,
            Line *e0, Line *e1, Line *e2,
            hash_table_ptr vtab, SegList *tlis, float *data_values )
{
    int      poly[3];
    Triangle *tp;

#ifdef WHITEBOX_TEST
histograms.polygonalizations[3]++;
#endif

    if ( !IVTX ( e0, 0 ) ||
         !IVTX ( e1, 1 ) ||
         !IVTX ( e2, 2 )   )
      goto error;

    TRI ( 0, 1, 2 );

    return OK;

    error:
        ERROR_SECTION;
        return ERROR;
}
