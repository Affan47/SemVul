Dataset_read_seq_info(Dataset *dataset, FILE *fp){
    register gint i, start, element_id, length, seq_offset;
    register Dataset_Sequence *ds;
    register BitArray *ba;
    register CompoundFile_Pos offset;
    register Sequence_Strand strand
        = (dataset->alphabet->type == Alphabet_Type_DNA)
        ? Sequence_Strand_FORWARD
        : Sequence_Strand_UNKNOWN;
    register CompoundFile_Location *location;
    for(i = 0; i < dataset->seq_list->len; i++){
        ds = dataset->seq_list->pdata[i];
        ba = BitArray_read(fp, dataset->width->seq_data_item_size);
        start = 0;
        element_id = BitArray_get(ba, start, dataset->width->num_db_width);
        start += dataset->width->num_db_width;
        offset = BitArray_get(ba, start, dataset->width->max_db_len_width);
        start += dataset->width->max_db_len_width;
        length = BitArray_get(ba, start, dataset->width->max_seq_len_width);
        start += dataset->width->max_seq_len_width;
        location = CompoundFile_Location_create(dataset->fdb->cf,
                                                offset, element_id);
        seq_offset = 1 + strlen(ds->id)
                   + (ds->def?strlen(ds->def)+1:0);
        ds->key = FastaDB_Key_create(dataset->fdb,
                                     location, strand,
                                     seq_offset, length);
        CompoundFile_Location_destroy(location);
        ds->gcg_checksum = BitArray_get(ba, start, 14);
        ds->pos = i;
        BitArray_destroy(ba);
        }
    return;
    }
