mca_pml_ob1_dump(struct ompi_communicator_t* comm, int verbose)
{
    struct mca_pml_comm_t* pml_comm = comm->c_pml_comm;
    int i;


    opal_output(0, "Communicator %s [%p](%d) rank %d recv_seq %d num_procs %lu last_probed %lu\n",
                comm->c_name, (void*) comm, comm->c_contextid, comm->c_my_rank,
                pml_comm->recv_sequence, pml_comm->num_procs, pml_comm->last_probed);
    if( opal_list_get_size(&pml_comm->wild_receives) ) {
        opal_output(0, "expected MPI_ANY_SOURCE fragments\n");
        mca_pml_ob1_dump_frag_list(&pml_comm->wild_receives, true);
    }


    for( i = 0; i < (int)pml_comm->num_procs; i++ ) {
        mca_pml_ob1_comm_proc_t* proc = &pml_comm->procs[i];
        mca_bml_base_endpoint_t* ep = (mca_bml_base_endpoint_t*)proc->ompi_proc->proc_endpoints[OMPI_PROC_ENDPOINT_TAG_BML];
        size_t n;

        opal_output(0, "[Rank %d] expected_seq %d ompi_proc %p send_seq %d\n",
                    i, proc->expected_sequence, (void*) proc->ompi_proc,
                    proc->send_sequence);

        if( opal_list_get_size(&proc->specific_receives) ) {
            opal_output(0, "expected specific receives\n");
            mca_pml_ob1_dump_frag_list(&proc->specific_receives, true);
        }
        if( opal_list_get_size(&proc->frags_cant_match) ) {
            opal_output(0, "out of sequence\n");
            mca_pml_ob1_dump_frag_list(&proc->frags_cant_match, false);
        }
        if( opal_list_get_size(&proc->unexpected_frags) ) {
            opal_output(0, "unexpected frag\n");
            mca_pml_ob1_dump_frag_list(&proc->unexpected_frags, false);
        }

        for( n = 0; n < ep->btl_eager.arr_size; n++ ) {
            mca_bml_base_btl_t* bml_btl = &ep->btl_eager.bml_btls[n];
            bml_btl->btl->btl_dump(bml_btl->btl, bml_btl->btl_endpoint, verbose);
        }
    }
    return OMPI_SUCCESS;
}
