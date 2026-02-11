Index_AddressList_write(Index_AddressList *address_list,
                                    Index *index){
    register gint i;
    register BitArray *ba = BitArray_create();
    register Index_Address *address;
    for(i = 0; i < address_list->found; i++){
        address = &address_list->address_list[i];
        BitArray_append(ba, address->sequence_id,
                        index->width->number_of_seqs_width);
        BitArray_append(ba, address->position,
                        index->dataset->width->max_seq_len_width);
        }
    BitArray_write(ba, index->fp);
    BitArray_destroy(ba);
    return;
    }
