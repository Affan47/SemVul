matchmap_store_destination (GncImportMatchMap *matchmap,
                            GNCImportTransInfo *trans_info,
                            gboolean use_match)
{
    GncImportMatchMap *tmp_matchmap = NULL;
    Account *dest;
    const char *descr, *memo;
    GList *tokens;
    gboolean useBayes;

    g_assert (trans_info);


    dest = ((use_match) ?
            xaccSplitGetAccount
            (xaccSplitGetOtherSplit
             (gnc_import_MatchInfo_get_split
              (gnc_import_TransInfo_get_selected_match (trans_info)))) :
            gnc_import_TransInfo_get_destacc (trans_info));
    if (dest == NULL)
        return;

    tmp_matchmap = ((matchmap != NULL) ?
                    matchmap :
                    gnc_imap_create_from_account
                    (xaccSplitGetAccount
                     (gnc_import_TransInfo_get_fsplit (trans_info))));


    useBayes = gnc_prefs_get_bool (GNC_PREFS_GROUP_IMPORT, GNC_PREF_USE_BAYES);
    if (useBayes)
    {

        tokens = TransactionGetTokens(trans_info);


        gnc_imap_add_account_bayes(tmp_matchmap, tokens, dest);

    }
    else
    {

        descr = xaccTransGetDescription
                (gnc_import_TransInfo_get_trans (trans_info));
        if (descr && (strlen (descr) > 0))
            gnc_imap_add_account (tmp_matchmap,
                                  GNCIMPORT_DESC,
                                  descr,
                                  dest);
        memo = xaccSplitGetMemo
               (gnc_import_TransInfo_get_fsplit (trans_info));
        if (memo && (strlen (memo) > 0))
            gnc_imap_add_account (tmp_matchmap,
                                  GNCIMPORT_MEMO,
                                  memo,
                                  dest);
    }

    if (matchmap == NULL)
        gnc_imap_destroy (tmp_matchmap);
}
