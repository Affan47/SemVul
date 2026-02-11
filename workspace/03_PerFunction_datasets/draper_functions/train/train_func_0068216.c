TN_DefaultName(GGadget *g, int r, int c) {
    struct gfi_data *d = GGadgetGetUserData(g);
    int rows;
    struct matrix_data *strings = GMatrixEditGet(g, &rows);

    if ( strings==NULL || !strings[3*r+2].user_bits )
return( NULL );

return( tn_recalculatedef(d,strings[3*r+1].u.md_ival ));
}
