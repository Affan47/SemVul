search_internal_pb (Slapi_PBlock *pb)
{
    plugin_search_internal_data   psid;
    Entry_Node                    *iterator, *tmp;
    Referral_Node                 *ref_iterator, *ref_tmp;
    int                           i;
    int                           opresult = 0;
    Slapi_Entry                   **pb_search_entries = NULL;
    char                          **pb_search_referrals = NULL;

	PR_ASSERT (pb);


    psid.rc              = -1;
    psid.num_entries     =0;
    psid.num_referrals   =0;
    psid.entry_list_head = NULL;
    psid.referral_list_head = NULL;


    slapi_pblock_set(pb, SLAPI_PLUGIN_INTOP_RESULT, &opresult);
    slapi_pblock_set(pb, SLAPI_PLUGIN_INTOP_SEARCH_ENTRIES, pb_search_entries);
    slapi_pblock_set(pb, SLAPI_PLUGIN_INTOP_SEARCH_REFERRALS, pb_search_referrals);


    search_internal_callback_pb (pb, &psid, internal_plugin_result_callback,
									  internal_plugin_search_entry_callback,
									  internal_plugin_search_referral_callback);
    opresult = psid.rc;


    pb_search_entries = (Slapi_Entry **)slapi_ch_calloc((psid.num_entries + 1), sizeof(Slapi_Entry *));

    for(i=0,iterator = psid.entry_list_head; iterator !=NULL; iterator=iterator->next, i++)
    {
        pb_search_entries[i]= iterator->data;
    }
    pb_search_entries[i]=NULL;


    iterator=psid.entry_list_head;
    while(iterator != NULL)
    {

        tmp                  = iterator;
        iterator             = iterator->next;


        if(tmp != NULL)
        {
            slapi_ch_free((void **) &tmp);
        }
    }
    psid.entry_list_head = NULL;


    if(psid.num_referrals != 0)
    {
        pb_search_referrals = (char **)slapi_ch_calloc((psid.num_referrals + 1), sizeof(char *));

        for(i=0, ref_iterator = psid.referral_list_head; ref_iterator !=NULL; ref_iterator=ref_iterator->next, i++)
        {
            pb_search_referrals[i]= ref_iterator->data;
        }
        pb_search_referrals[i]=NULL;


        ref_iterator=psid.referral_list_head;
        while(ref_iterator != NULL)
        {

            ref_tmp              = ref_iterator;
            ref_iterator         = ref_iterator->next;


            if(ref_tmp != NULL)
            {
                slapi_ch_free((void **) &ref_tmp);
            }
	}
	psid.referral_list_head = NULL;
    }


    slapi_pblock_set(pb, SLAPI_NENTRIES, &psid.num_entries);
    slapi_pblock_set(pb, SLAPI_PLUGIN_INTOP_RESULT, &opresult);
    slapi_pblock_set(pb, SLAPI_PLUGIN_INTOP_SEARCH_ENTRIES, pb_search_entries);
    slapi_pblock_set(pb, SLAPI_PLUGIN_INTOP_SEARCH_REFERRALS, pb_search_referrals);

	return 0;
}
