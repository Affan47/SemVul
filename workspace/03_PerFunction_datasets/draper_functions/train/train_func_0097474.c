newForsPAF(const char *name, const char *type, const char *id,
                  const char *desc)
{

    ForsPAF *paf;
    int     pos = 0;


    if (!name || !type)
        return NULL;

    paf = (ForsPAF *)cpl_malloc(sizeof(ForsPAF));
    if (paf) {
        paf->header = _forsPAFHeaderCreate(name, type, id, desc, &pos);
        paf->records = NULL;
        paf->nh = pos;
        paf->nr = 0;
        paf->name = cpl_strdup(name);
    }

    return paf;

}
