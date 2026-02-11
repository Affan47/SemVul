mca_coll_hierarch_module_destruct(mca_coll_hierarch_module_t *hierarch_module)
{
    int i, size;
    struct mca_coll_hierarch_llead_t *current=NULL;

    if ( MPI_COMM_NULL != hierarch_module->hier_lcomm ) {
	ompi_comm_free (&(hierarch_module->hier_lcomm) );
    }
    if ( NULL != hierarch_module->hier_reqs ) {
	free ( hierarch_module->hier_reqs );
    }

    size = opal_pointer_array_get_size ( &(hierarch_module->hier_llead));
    for ( i=0; i<size; i++) {
        current = (struct mca_coll_hierarch_llead_t *)opal_pointer_array_get_item (
                  &(hierarch_module->hier_llead), i ) ;

        if ( NULL == current ) {
            continue;
        }

        if ( NULL != current->lleaders ) {
            free ( current->lleaders );
        }
	if ( MPI_COMM_NULL != current->llcomm ){
	    ompi_comm_free ( &(current->llcomm));
	}
        free ( current );
    }
    opal_pointer_array_remove_all ( &(hierarch_module->hier_llead));
    OBJ_DESTRUCT (&(hierarch_module->hier_llead));

    if ( NULL != hierarch_module->hier_colorarr ) {
	free ( hierarch_module->hier_colorarr );
    }
    if ( NULL != hierarch_module->hier_llr ) {
	free ( hierarch_module->hier_llr);
    }

    return;
}
