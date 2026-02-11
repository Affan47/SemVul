Index_seed_HSPsets(Index *index, Index_Strand *index_strand,
                                     GArray *seed_list, HSP_Param *hsp_param,
                                     Sequence *query, gboolean revcomp_target,
                                     GArray *interval_list){
    register GPtrArray *hsp_set_list = g_ptr_array_new();
    register gint i, j, word_id, address_list_len;
    gint target_id;
    register Index_WordSeed *seed;
    register Index_Address *address_list;
    register Index_Word *index_word;
    register HSPset_SList_Node *node, **target_bin
        = g_new0(HSPset_SList_Node*, index->dataset->header->number_of_seqs);


    register GArray *target_id_list = g_array_new(FALSE, FALSE, sizeof(gint));
    register HSPset *hsp_set;
    register Index_HSPset *index_hsp_set;
    register RecycleBin *hsp_slist_recycle = HSPset_SList_RecycleBin_create();

    for(i = 0; i < seed_list->len; i++){
        seed = &g_array_index(seed_list, Index_WordSeed, i);
        word_id = index_strand->word_table[seed->leaf];
        index_word = &index_strand->word_list[word_id];
        g_assert(word_id >= 0);

        address_list = g_new(Index_Address, index_word->freq_count);
        address_list_len = Index_Word_get_address_list(index, index_strand,
                                                   index_word, address_list,
                                                   interval_list);
        if(!address_list_len){
            g_free(address_list);
            continue;
            }
        g_assert(index_word->freq_count);
        g_assert(address_list_len);
        for(j = 0; j < address_list_len; j++){
            target_id = address_list[j].sequence_id;
            if(!target_bin[target_id])
                g_array_append_val(target_id_list, target_id);
            target_bin[target_id]
                = HSPset_SList_append(hsp_slist_recycle, target_bin[target_id],
                       seed->query_pos, address_list[j].position);
            }
        g_free(address_list);
        }
    for(i = 0; i < target_id_list->len; i++){
        target_id = g_array_index(target_id_list, gint, i);
        node = target_bin[target_id];
        g_assert(node);
        hsp_set = Index_get_HSPset(index, target_id, hsp_param, query,
                                   node, revcomp_target);
        if(hsp_set){
            index_hsp_set = Index_HSPset_create(hsp_set, target_id);
            HSPset_destroy(hsp_set);

            g_ptr_array_add(hsp_set_list, index_hsp_set);
            }
        }
    g_free(target_bin);
    g_array_free(target_id_list, TRUE);
    RecycleBin_destroy(hsp_slist_recycle);
    if(!hsp_set_list->len){
        g_ptr_array_free(hsp_set_list, TRUE);
        return NULL;
        }
    return hsp_set_list;
    }
