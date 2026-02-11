recv_req_match_wild( mca_pml_ob1_recv_request_t* req,
                     mca_pml_ob1_comm_proc_t **p)
{
    mca_pml_ob1_comm_t* comm = req->req_recv.req_base.req_comm->c_pml_comm;
    mca_pml_ob1_comm_proc_t* proc = comm->procs;
    size_t i;


    for (i = comm->last_probed + 1; i < comm->num_procs; i++) {
        mca_pml_ob1_recv_frag_t* frag;


        if((frag = recv_req_match_specific_proc(req, &proc[i]))) {
            *p = &proc[i];
            comm->last_probed = i;
            req->req_recv.req_base.req_proc = proc[i].ompi_proc;
            prepare_recv_req_converter(req);
            return frag;
        }
    }
    for (i = 0; i <= comm->last_probed; i++) {
        mca_pml_ob1_recv_frag_t* frag;


        if((frag = recv_req_match_specific_proc(req, &proc[i]))) {
            *p = &proc[i];
            comm->last_probed = i;
            req->req_recv.req_base.req_proc = proc[i].ompi_proc;
            prepare_recv_req_converter(req);
            return frag;
        }
    }

    *p = NULL;
    return NULL;
}
