Dataset_Header_create(Alphabet_Type alphabet_type,
                                             gboolean softmask_input){
    register Dataset_Header *header = g_new0(Dataset_Header, 1);
    header->magic = DATASET_HEADER_MAGIC;
    header->version = DATASET_HEADER_VERSION;
    header->type = ((alphabet_type == Alphabet_Type_DNA)?1:0)
                 | ((softmask_input?1:0) << 1);

    return header;
    }
