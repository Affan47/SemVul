rmaps_lama_ok_to_prune_level(rmaps_lama_level_type_t level)
{
    int i;

    for( i = 0; i < lama_mapping_num_layouts; ++i ) {
        if( level == lama_mapping_layout[i] ) {
            return false;
        }
    }

    return true;
}
