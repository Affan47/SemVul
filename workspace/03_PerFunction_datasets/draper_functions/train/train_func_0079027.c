hawki_step_stats_save
(cpl_table         ** target_stats,
 cpl_parameterlist *  recipe_parlist,
 cpl_frameset      *  recipe_frameset,
 cpl_frameset      *  used_frameset,
 cpl_propertylist  ** stats_stats,
 const char        *  calpro,
 const char        *  protype)
{
    const cpl_frame  *  reference_frame;
    cpl_propertylist *  referencelist;
    cpl_propertylist ** extlists;
    int                 idet;
    int                 ext_nb;
    const char       *  recipe_name = "hawki_step_stats";
    cpl_errorstate      error_prevstate = cpl_errorstate_get();


    reference_frame = cpl_frameset_get_first_const(used_frameset);


    cpl_msg_info(__func__, "Creating the keywords list") ;
    referencelist = cpl_propertylist_load_regexp
        (cpl_frame_get_filename(reference_frame), 0,HAWKI_HEADER_EXT_FORWARD,0);
    extlists =
        cpl_malloc(HAWKI_NB_DETECTORS * sizeof(cpl_propertylist*));
    for (idet=0 ; idet<HAWKI_NB_DETECTORS ; idet++)
    {

        ext_nb=hawki_get_ext_from_detector
            (cpl_frame_get_filename(reference_frame), idet+1);


        extlists[idet] = cpl_propertylist_load_regexp(
                cpl_frame_get_filename(reference_frame), ext_nb,
                HAWKI_HEADER_EXT_FORWARD, 0);


        cpl_propertylist_append(extlists[idet],stats_stats[idet]);
    }


    hawki_tables_save(recipe_frameset,
                      recipe_parlist,
                      used_frameset,
                      (const cpl_table **)target_stats,
                      recipe_name,
                      calpro,
                      protype,
                      (const cpl_propertylist*)referencelist,
                      (const cpl_propertylist**)extlists,
                      "hawki_step_stats.fits");


    cpl_propertylist_delete(referencelist) ;
    for (idet=0 ; idet<HAWKI_NB_DETECTORS ; idet++)
    {
        cpl_propertylist_delete(extlists[idet]) ;
    }
    cpl_free(extlists) ;

    if(!cpl_errorstate_is_equal(error_prevstate))
    {
        cpl_errorstate_set(CPL_ERROR_NONE);
        return -1;
    }
    return  0;
}
