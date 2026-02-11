removezeros(ADIOI_Flatlist_node *flat_type)
{
    int i,j,opt_blocks;
    ADIO_Offset *opt_blocklens;
    ADIO_Offset *opt_indices;


    if (flat_type->count <= 2) return;

    opt_blocks = 2;
    for (i=1; i < flat_type->count -1; i++) {
        if(flat_type->blocklens[i] != 0)
	    opt_blocks++;
    }

    if (opt_blocks == flat_type->count) return;
    opt_blocklens = (ADIO_Offset *) ADIOI_Malloc(opt_blocks * sizeof(ADIO_Offset));
    opt_indices = (ADIO_Offset *)ADIOI_Malloc(opt_blocks*sizeof(ADIO_Offset));


    opt_blocklens[0] = flat_type->blocklens[0];
    opt_indices[0] = flat_type->indices[0];
    j = 1;
    for (i=1; i< flat_type->count -1; i++) {
	if( flat_type->blocklens[i] != 0) {
		opt_indices[j] = flat_type->indices[i];
		opt_blocklens[j] = flat_type->blocklens[i];
		j++;
	}
    }
    opt_indices[j] = flat_type->indices[flat_type->count -1];
    opt_blocklens[j] = flat_type->blocklens[flat_type->count -1];

    flat_type->count = opt_blocks;
    ADIOI_Free(flat_type->blocklens);
    ADIOI_Free(flat_type->indices);
    flat_type->blocklens = opt_blocklens;
    flat_type->indices = opt_indices;
    return;
}
