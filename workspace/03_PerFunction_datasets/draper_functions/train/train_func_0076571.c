ompi_osc_rdma_module_get(void *origin_addr,
                          int origin_count,
                          struct ompi_datatype_t *origin_dt,
                          int target,
                          OPAL_PTRDIFF_TYPE target_disp,
                          int target_count,
                          struct ompi_datatype_t *target_dt,
                          ompi_win_t *win)
{
    int ret;
    ompi_osc_rdma_sendreq_t *sendreq;
    ompi_osc_rdma_module_t *module = GET_MODULE(win);

    if ((OMPI_WIN_STARTED & ompi_win_get_mode(win)) &&
        (!module->m_sc_remote_active_ranks[target])) {
        return MPI_ERR_RMA_SYNC;
    }

    if (OMPI_WIN_FENCE & ompi_win_get_mode(win)) {

        ompi_win_set_mode(win, OMPI_WIN_FENCE | OMPI_WIN_ACCESS_EPOCH |
                          OMPI_WIN_EXPOSE_EPOCH);
    }


    if (0 == origin_count || 0 == target_count) {
            return OMPI_SUCCESS;
    }


    ret = ompi_osc_rdma_sendreq_alloc_init(OMPI_OSC_RDMA_GET,
                                           origin_addr,
                                           origin_count,
                                           origin_dt,
                                           target,
                                           target_disp,
                                           target_count,
                                           target_dt,
                                           module,
                                           &sendreq);
    MEMCHECKER(
        memchecker_convertor_call(&opal_memchecker_base_mem_noaccess,
                                  &sendreq->req_origin_convertor);
    );
    if (OMPI_SUCCESS != ret) return ret;

    if (module->m_eager_send_active) {
        OPAL_THREAD_LOCK(&module->m_lock);
        sendreq->req_module->m_num_pending_out += 1;
        module->m_num_pending_sendreqs[sendreq->req_target_rank] += 1;
        OPAL_THREAD_UNLOCK(&(module->m_lock));

        ret  = ompi_osc_rdma_sendreq_send(module, sendreq);

        if (OMPI_ERR_TEMP_OUT_OF_RESOURCE == ret) {
            OPAL_THREAD_LOCK(&module->m_lock);
            sendreq->req_module->m_num_pending_out -= 1;
            opal_list_append(&(module->m_pending_sendreqs),
                             (opal_list_item_t*) sendreq);
            OPAL_THREAD_UNLOCK(&module->m_lock);
            ret = OMPI_SUCCESS;
        }
    } else {

        ret = enqueue_sendreq(module, sendreq);
    }

    return ret;
}
