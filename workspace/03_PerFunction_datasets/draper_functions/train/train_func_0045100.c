Index_Strand_write(Index *index, Index_Strand *index_strand){
    register BitArray *word_ba = BitArray_create();
    register gint i, word_id, word_count = 0;
    register Index_Word *index_word;

    Index_Strand_Header_print(&index_strand->header, index->fp);
    for(i = 0; i < index->vfsm->lrw; i++){
        word_id = index_strand->word_table[i];
        if(word_id >= 0){
            BitArray_append(word_ba, i,
                            index->width->max_word_width);
            index_word = &index_strand->word_list[word_id];
            BitArray_append(word_ba, index_word->freq_count,
                            index_strand->width.max_index_len_width);
            BitArray_append(word_ba, index_word->index_offset,
                            index_strand->width.total_index_len_width);
            word_count++;
            }
        }
    g_assert(word_count == index_strand->header.word_list_length);
    BitArray_write(word_ba, index->fp);
    BitArray_destroy(word_ba);
    return;
    }
