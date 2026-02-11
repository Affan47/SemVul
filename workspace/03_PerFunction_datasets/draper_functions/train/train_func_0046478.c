Index_memory_usage(Index *index){
    g_assert(index);
    return sizeof(Index)
         + sizeof(Index_Header)
         + (sizeof(gchar)*index->header->dataset_path_len)
         + Dataset_memory_usage(index->dataset)
         + sizeof(Index_Width)
         + sizeof(VFSM)
         + (index->forward?Index_Strand_memory_usage(index->forward,
                                                     index->vfsm):0)
         + (index->revcomp?Index_Strand_memory_usage(index->forward,
                                                     index->vfsm):0);
    }
