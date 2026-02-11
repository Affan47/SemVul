gnc_import_TransInfo_init_matches (GNCImportTransInfo *trans_info,
                                   GNCImportSettings *settings)
{
    GNCImportMatchInfo * best_match = NULL;
    g_assert (trans_info);


    gnc_import_find_split_matches(trans_info,
                                  gnc_import_Settings_get_display_threshold (settings),
                                  gnc_import_Settings_get_fuzzy_amount (settings),
                                  gnc_import_Settings_get_match_date_hardlimit (settings));

    if (trans_info->match_list != NULL)
    {
        trans_info->match_list = g_list_sort(trans_info->match_list,
                                             compare_probability);
        best_match = g_list_nth_data(trans_info->match_list, 0);
        gnc_import_TransInfo_set_selected_match (trans_info,
                best_match,
                FALSE);
        if (best_match != NULL &&
                best_match->probability >= gnc_import_Settings_get_clear_threshold(settings))
        {
            trans_info->action = GNCImport_CLEAR;
            trans_info->selected_match_info = best_match;
        }
        else if (best_match == NULL ||
                 best_match->probability <= gnc_import_Settings_get_add_threshold(settings))
        {
            trans_info->action = GNCImport_ADD;
        }
        else if (gnc_import_Settings_get_action_skip_enabled(settings))
        {
            trans_info->action = GNCImport_SKIP;
        }
        else if (gnc_import_Settings_get_action_update_enabled(settings))
        {
            trans_info->action = GNCImport_UPDATE;
        }
        else
        {
            trans_info->action = GNCImport_ADD;
        }
    }
    else
    {
        trans_info->action = GNCImport_ADD;
    }
    if (best_match &&
            trans_info->action == GNCImport_CLEAR &&
            gnc_import_Settings_get_action_update_enabled(settings))
    {
        if (best_match->update_proposed)
        {
            trans_info->action = GNCImport_UPDATE;
        }
    }

    trans_info->previous_action = trans_info->action;
}
