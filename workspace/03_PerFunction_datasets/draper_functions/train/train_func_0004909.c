insert(AD_SPECIES *ad_species,AD_ALI *ad_ali)
{
    if (element(ad_species,ad_ali)) return 0;

    CLISTENTRY *newentry;
    newentry         = new CLISTENTRY;
    newentry->entry  = ad_species;
    newentry->entry2 = ad_ali;
    newentry->next   = first;

    first = newentry;
    anzahl ++;
    return 1;
}
