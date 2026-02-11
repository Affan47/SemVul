CheckTOCCache(time_t timestamp, STORAGECLASS tokenclass)
{
    CAFTOCL2CACHE *l2;
    CAFTOCL1CACHE *l1;
    CAFTOCCACHEENT *cent;
    unsigned char tmp;

    if (TOCCache[tokenclass] == NULL) return NULL;

    tmp = (timestamp>>16) & 0xff;
    l2 = TOCCache[tokenclass]->l2ptr[tmp];
    if (l2 == NULL) return NULL;

    tmp = (timestamp>>8) & 0xff;
    l1 = l2->l1ptr[tmp];
    if (l1 == NULL) return NULL;

    tmp = (timestamp) & 0xff;
    cent = l1->entries[tmp];

    ++TOCCacheHits;
    return cent;
}
