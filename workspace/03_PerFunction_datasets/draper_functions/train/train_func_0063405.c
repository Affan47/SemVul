add_to_invoke_table(mca_bcol_base_module_t *bcol_module,
                       mca_bcol_base_coll_fn_desc_t *fn_filtered,
                       mca_coll_ml_module_t *ml_module)
{
    struct mca_bcol_base_coll_fn_invoke_attributes_t *inv_attribs = NULL;
    int bcoll_type, data_src_type, waiting_semantic;
    int range_min,range_max;
    int i=0,j=0,k=0,mask=1;


    if((NULL == fn_filtered->inv_attr)||(NULL == fn_filtered->comm_attr)) {
        return OMPI_ERROR;
    }

    ML_VERBOSE(10, ("Calling add_to_invoke_table %p",fn_filtered->coll_fn));

    inv_attribs = fn_filtered->inv_attr;
    bcoll_type = fn_filtered->comm_attr->bcoll_type;
    data_src_type = fn_filtered->comm_attr->data_src;
    waiting_semantic = fn_filtered->comm_attr->waiting_semantics;

    range_min = msg_to_range(inv_attribs->bcol_msg_min);
    range_max = msg_to_range(inv_attribs->bcol_msg_max);

    for (j=0; j<OMPI_OP_NUM_OF_TYPES; j++) {
        for (k=0; k<OMPI_DATATYPE_MAX_PREDEFINED; k++) {

            if ((inv_attribs->datatype_bitmap & (mask << k)) && (inv_attribs->op_types_bitmap & (mask << j))){

               for (i=range_min; i<=range_max; i++) {
                    bcol_module->filtered_fns_table[data_src_type][waiting_semantic][bcoll_type][i][j][k]
                                                                    = fn_filtered;
                    ML_VERBOSE(21, ("Putting functions %d %d %d %d %p", bcoll_type, i, j, k, fn_filtered));
               }
            }
        }
    }

    return 0;

}
