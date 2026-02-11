search_top_layer_for_hetero_stasche(Hetero_Stasche **sinfo_vec)
{
    int i;
    int max = get_max_mtg_id() + 1;
    Hmdf_table *hmdf;

    construct_IntSet(hetero_top_layer, get_max_mtg_id() + 1);
    for (i = 1; i < max; i++) {


        if (sinfo_vec[i] == NULL) {
            continue;
        }
        hmdf = sinfo_vec[i]->hmdf_block->hmdf;
        if (hmdf != NULL
            && in_IntSet(hetero_layer, i)
            && is_top_layer_of_hetero_stasche(hmdf) ) {
            add1_IntSet(hetero_top_layer, i);
        }
    }
}
