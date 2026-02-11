create(AD_SPECIES * adptr1,AD_ALI *adptr2)
{
    GBDATA *erg =  GBT_add_data(adptr1->gb_species,adptr2->name(),"data", GB_STRING);
    if (!erg) return new AD_ERR(GB_await_error());
    return this->init(adptr1,adptr2);
}
