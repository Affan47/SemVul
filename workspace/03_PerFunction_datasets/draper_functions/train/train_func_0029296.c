mm_free(mm_t mm) {
    int i, j, *nlist = NULL;
    mod_instance_t **list = NULL, mi;


    xhash_walk(mm->modules, _mm_reaper, NULL);


    for(i = 0; i < 13; i++) {
        switch(i) {
            case 0:
                list = &mm->sess_start;
                nlist = &mm->nsess_start;
                break;
            case 1:
                list = &mm->sess_end;
                nlist = &mm->nsess_end;
                break;
            case 2:
                list = &mm->in_sess;
                nlist = &mm->nin_sess;
                break;
            case 3:
                list = &mm->in_router;
                nlist = &mm->nin_router;
                break;
            case 4:
                list = &mm->out_sess;
                nlist = &mm->nout_sess;
                break;
            case 5:
                list = &mm->out_router;
                nlist = &mm->nout_router;
                break;
            case 6:
                list = &mm->pkt_sm;
                nlist = &mm->npkt_sm;
                break;
            case 7:
                list = &mm->pkt_user;
                nlist = &mm->npkt_user;
                break;
            case 8:
                list = &mm->pkt_router;
                nlist = &mm->npkt_router;
                break;
            case 9:
                list = &mm->user_load;
                nlist = &mm->nuser_load;
                break;
            case 10:
                list = &mm->user_create;
                nlist = &mm->nuser_create;
                break;
            case 11:
                list = &mm->user_delete;
                nlist = &mm->nuser_delete;
                break;
            case 12:
                list = &mm->disco_extend;
                nlist = &mm->ndisco_extend;
                break;
        }

        for(j = 0; j < *nlist; j++) {
            mi = (*list)[j];
            if(mi->arg != NULL)
                free(mi->arg);
            free(mi);
        }
    }


    free(mm->sess_start);
    free(mm->sess_end);
    free(mm->in_sess);
    free(mm->in_router);
    free(mm->out_sess);
    free(mm->out_router);
    free(mm->pkt_sm);
    free(mm->pkt_user);
    free(mm->pkt_router);
    free(mm->user_load);
    free(mm->user_create);
    free(mm->user_delete);
    free(mm->disco_extend);

    xhash_free(mm->modules);

    free(mm);
}
