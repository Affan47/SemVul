cc_of_set_real_dpid_auxid(uint64_t dummy_dpid, uint8_t dummy_auxid,
                          uint64_t dp_id, uint8_t aux_id)
{
    cc_of_ret status = CC_OF_OK;
    cc_ofchannel_info_t *ofchann_info_old = NULL;
    cc_ofchannel_info_t ofchann_info_new;
    cc_ofchannel_key_t ofchann_key_old, ofchann_key_new;
    gboolean new_entry;
    gpointer chht_key = NULL, chht_info = NULL;

    ofchann_key_new.dp_id = dp_id;
    ofchann_key_new.aux_id = aux_id;
    ofchann_key_old.dp_id = dummy_dpid;
    ofchann_key_old.aux_id = dummy_auxid;

    g_mutex_lock(&cc_of_global.ofchannel_htbl_lock);
    if (g_hash_table_lookup_extended(cc_of_global.ofchannel_htbl,
                                     &ofchann_key_old,
                                     &chht_key, &chht_info) == FALSE) {


        ofchann_key_old.aux_id = dummy_dpid;
        if (g_hash_table_lookup_extended(cc_of_global.ofchannel_htbl,
                                         &ofchann_key_old,
                                         &chht_key, &chht_info) == FALSE) {
			CC_LOG_ERROR("%s(%d):, could not find ofchann_info in ofchannel_htbl"
				         "for key dummy_dpid-%lu, dummy_auxid-%u",__FUNCTION__,
					     __LINE__, dummy_dpid, dummy_auxid);
			g_mutex_unlock(&cc_of_global.ofchannel_htbl_lock);
			return CC_OF_EINVAL;
		}
    }
    print_ofchann_htbl();

    ofchann_info_old = (cc_ofchannel_info_t *)chht_info;
	CC_LOG_DEBUG("%s(%d):ofchannel info -%p",
                __FUNCTION__, __LINE__, ofchann_info_old);


    memcpy(&ofchann_info_new, ofchann_info_old, sizeof(cc_ofchannel_info_t));
    status = del_ofchann_rwsocket_lockfree((int)dummy_dpid);
	print_ofchann_htbl();
    update_global_htbl_lockfree(OFCHANN, ADD, (gpointer)&ofchann_key_new,
                       &ofchann_info_new, &new_entry);
    print_ofchann_htbl();
	g_mutex_unlock(&cc_of_global.ofchannel_htbl_lock);
    return status;
}
