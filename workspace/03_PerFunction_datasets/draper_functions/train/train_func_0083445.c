Alignment_get_gene_orientation(Alignment *alignment){
    register gint i;
    register AlignmentOperation *ao;
    for(i = 0; i < alignment->operation_list->len; i++){
        ao = alignment->operation_list->pdata[i];
        if(ao->transition->label == C4_Label_5SS)
            return '+';
        if(ao->transition->label == C4_Label_3SS)
            return '-';
        }
    return '.';
    }
