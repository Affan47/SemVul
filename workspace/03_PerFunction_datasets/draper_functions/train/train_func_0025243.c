error()


{

    if (count > 0) {
        return new AD_ERR("AD_SPECIES: existing Subobjects ! No change of species allowed\n",CORE);
    }
    if (last == 1)
        return new AD_ERR("AD_SPECIES: already at EOF !",CORE);
    return 0;
}
