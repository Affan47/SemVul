zc_crk_ptext_unref(struct zc_crk_ptext *ptext)
{
    if (!ptext)
        return NULL;
    ptext->refcount--;
    if (ptext->refcount > 0)
        return ptext;
    dbg(ptext->ctx, "ptext %p released\n", ptext);
    key_table_free(ptext->key2);
    key2r_free(ptext->k2r);
    free(ptext);
    return NULL;
}
