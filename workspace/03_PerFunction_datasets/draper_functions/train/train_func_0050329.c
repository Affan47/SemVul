exit()
{
    if (ad_species && gb_ali) {
        ad_species->count --;
        ad_ali->count --;
        con_remove(ad_species,ad_ali);
    }
    ad_species = 0;ad_ali = 0;
    AD_READWRITE::gbdataptr = 0;
    return 0;
}
