C4_Label_get_name(C4_Label label){
    register gchar *name = NULL;
    switch(label){
        case C4_Label_NONE:
            name = "none";
            break;
        case C4_Label_MATCH:
            name = "match";
            break;
        case C4_Label_GAP:
            name = "gap";
            break;
        case C4_Label_NER:
            name = "ner";
            break;
        case C4_Label_5SS:
            name = "5'ss";
            break;
        case C4_Label_3SS:
            name = "3'ss";
            break;
        case C4_Label_INTRON:
            name = "intron";
            break;
        case C4_Label_SPLIT_CODON:
            name = "split codon";
            break;
        case C4_Label_FRAMESHIFT:
            name = "frameshift";
            break;
        default:
            g_error("Unknown label [%d]", label);
            break;
        }
    return name;
    }
