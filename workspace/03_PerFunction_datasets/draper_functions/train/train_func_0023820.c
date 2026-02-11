start_upload() {


    set<VDA_CHUNK_HOST*>::iterator i;
    for (i=hosts.begin(); i!=hosts.end(); i++) {
        CHUNK_ON_HOST* c = (CHUNK_ON_HOST*)*i;
        if (c->transfer_in_progress) return 0;
    }
    CHUNK_ON_HOST* c = (CHUNK_ON_HOST*)*(hosts.begin());
    c->start_upload();
    return 0;
}
