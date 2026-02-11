row_c2perl_int(pTHX_ int * row, int ncols) {

    int j;
    AV * row_av = newAV();
    for(j=0; j<ncols; ++j) {
        av_push(row_av, newSVnv(row[j]));
    }
    return ( newRV_noinc( (SV*) row_av ) );
}
