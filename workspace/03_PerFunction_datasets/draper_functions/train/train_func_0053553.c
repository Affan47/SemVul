rd_from_dl(rd_t* r, dl* l) {
    int i;
    rd_alloc_data(r, dl_size(l)/2);
    for (i=0; i<r->N; i++) {
        r->ra [i] = dl_get(l, i*2);
        r->dec[i] = dl_get(l, i*2+1);
    }
}
