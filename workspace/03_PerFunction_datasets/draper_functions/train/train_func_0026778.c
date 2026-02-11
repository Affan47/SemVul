mca_pml_ob1_dump(struct ompi_communicator_t* comm, int verbose)
{
    struct mca_pml_comm_t* pml_comm = comm->c_pml_comm;
    int i;


    for( i = 0; i < (int)pml_comm->num_procs; i++ ) {
        mca_pml_ob1_comm_proc_t* proc = &pml_comm->procs[i];
        mca_bml_base_endpoint_t* ep = (mca_bml_base_endpoint_t*)proc->ompi_proc->proc_endpoints[OMPI_PROC_ENDPOINT_TAG_BML];
        size_t n;

        opal_output(0, "[Rank %d]\n", i);


        for(n=0; n<ep->btl_eager.arr_size; n++) {
            mca_bml_base_btl_t* bml_btl = &ep->btl_eager.bml_btls[n];
            bml_btl->btl->btl_dump(bml_btl->btl, bml_btl->btl_endpoint, verbose);
        }
    }
    return OMPI_SUCCESS;
}
