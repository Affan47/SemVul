fs_binding_truncate(fs_binding *b, int length)
{
    for (int i=0; b[i].name; i++) {
        fs_rid_vector_truncate(b[i].vals, length);
    }
}
