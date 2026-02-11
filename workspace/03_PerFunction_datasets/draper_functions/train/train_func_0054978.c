ED4_compression_toggle_changed_cb(AW_root *root, AW_CL cd1, AW_CL )
{


    int gaps = root->awar(ED4_AWAR_COMPRESS_SEQUENCE_GAPS)->read_int();
    int hide = root->awar(ED4_AWAR_COMPRESS_SEQUENCE_HIDE)->read_int();
    ED4_remap_mode mode = ED4_remap_mode(root->awar(ED4_AWAR_COMPRESS_SEQUENCE_TYPE)->read_int());

    switch(int(cd1)) {
        case 0: {
            if (gaps!=2 && hide!=0) {
                root->awar(ED4_AWAR_COMPRESS_SEQUENCE_HIDE)->write_int(0);
                return;
            }
            break;
        }
        case 1: {
            if (hide!=0 && gaps!=2) {
                root->awar(ED4_AWAR_COMPRESS_SEQUENCE_GAPS)->write_int(2);
                return;
            }
            break;
        }
        default: {
            e4_assert(0);
            break;
        }
    }

    mode = ED4_RM_NONE;
    switch (gaps) {
        case 0: mode = ED4_RM_NONE; break;
        case 1: mode = ED4_RM_DYNAMIC_GAPS; break;
        case 2: {
            switch(hide) {
                case 0: mode = ED4_RM_MAX_ALIGN; break;
                case 1: mode = ED4_RM_SHOW_ABOVE; break;
                default: e4_assert(0); break;
            }
            break;
        }
        default: e4_assert(0); break;
    }

    root->awar(ED4_AWAR_COMPRESS_SEQUENCE_TYPE)->write_int(int(mode));
}
