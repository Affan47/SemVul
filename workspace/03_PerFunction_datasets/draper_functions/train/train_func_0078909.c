slapi_unregister_backend_state_change(void * handle)
{
    struct mtn_be_ch_list * cur_be_ch_plg = mtn_plug_list;
    struct mtn_be_ch_list * prev_be_ch_plg = mtn_plug_list;
    while (cur_be_ch_plg)
    {
        if (cur_be_ch_plg->handle == handle)
        {
            if (cur_be_ch_plg == mtn_plug_list)
            {
                mtn_plug_list = mtn_plug_list->next;
                slapi_ch_free((void **) &cur_be_ch_plg);
                return 0;
            }
            else
            {
                prev_be_ch_plg->next = cur_be_ch_plg->next;
                slapi_ch_free((void **) &cur_be_ch_plg);
                return 0;
            }
        }
        prev_be_ch_plg = cur_be_ch_plg;
        cur_be_ch_plg = cur_be_ch_plg->next;
    }
    return 1;
}
