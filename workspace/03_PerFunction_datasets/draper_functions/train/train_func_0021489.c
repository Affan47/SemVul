fitsbin_read(fitsbin_t* fb) {
    int i;

    for (i=0; i<nchunks(fb); i++) {
        fitsbin_chunk_t* chunk = get_chunk(fb, i);
        if (read_chunk(fb, chunk)) {
            if (chunk->required)
                goto bailout;
        }
    }
    return 0;

 bailout:
    return -1;
}
