gnc_AB_BANKING_fini(AB_BANKING *api)
{
    if (api == gnc_AB_BANKING)
    {
        if (--gnc_AB_BANKING_refcount == 0)
        {
#ifdef AQBANKING_VERSION_5_PLUS
            if (gnc_gwengui_extended_by_ABBanking)
                AB_Gui_Unextend(gnc_gwengui_extended_by_ABBanking);
            gnc_gwengui_extended_by_ABBanking = NULL;
#endif
            return AB_Banking_Fini(api);
        }
    }
    else
    {
#ifdef AQBANKING_VERSION_5_PLUS
        if (gnc_gwengui_extended_by_ABBanking)
            AB_Gui_Unextend(gnc_gwengui_extended_by_ABBanking);
        gnc_gwengui_extended_by_ABBanking = NULL;
#endif
        return AB_Banking_Fini(api);
    }
    return 0;
}
