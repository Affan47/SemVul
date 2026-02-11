ns_ref_efuns(_ns_efuns ** ss)
{
    if (ss && *ss) {
        (*ss)->refcount++;
        return *ss;
    }
    return NULL;
}
