btreePageCompressPribucket(AjPBtpage page,
                                       const AjPTable newpostable)
{
    unsigned char* buf = page->buf;
    ajuint nentries;
    ajulong overflow = 0UL;
    unsigned char *idptr = NULL;
    unsigned char *keyptr = NULL;
    ajuint klen;
    ajuint i;
    ajulong lv;
    unsigned char * lp = NULL;

    buf = page->buf;

    GBT_BUCKNENTRIES(buf,&nentries);
    GBT_BUCKOVERFLOW(buf,&overflow);


    keyptr = PBT_BUCKKEYLEN(buf);
    idptr = keyptr + (nentries * sizeof(ajuint));

    for(i=0;i<nentries;i++)
    {
	BT_GETAJUINT(keyptr,&klen);
	idptr += klen;
        lp = idptr - 8;
        BT_GETAJULONG(lp,&lv);

        if(lv)
        {
            lv = btreePageposCompress(lv, newpostable,
                                      "Pribucket keypos");
            BT_SETAJULONG(lp, lv);
        }

	keyptr += sizeof(ajuint);
    }

    return;
}
