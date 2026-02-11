init_convert_1_0_0_to_1_1_0(struct _proc **procs, int nprocs,
                            int *max_tag, int *max_cid)
{
  const lam_ssi_rpi_actions_1_0_0_t *actions_1_0_0;


  actions_1_0_0 = init_1_0_0(procs, nprocs, max_tag, max_cid);
  if (actions_1_0_0 == NULL)
    return NULL;


  actions_1_1_0.lsra_addprocs = actions_1_0_0->lsra_addprocs;
  actions_1_1_0.lsra_finalize = actions_1_0_0->lsra_finalize;

  actions_1_1_0.lsra_build = actions_1_0_0->lsra_build;
  actions_1_1_0.lsra_start = actions_1_0_0->lsra_start;
  actions_1_1_0.lsra_advance = actions_1_0_0->lsra_advance;
  actions_1_1_0.lsra_destroy = actions_1_0_0->lsra_destroy;

  actions_1_1_0.lsra_iprobe = actions_1_0_0->lsra_iprobe;

  actions_1_1_0.lsra_fastrecv = actions_1_0_0->lsra_fastrecv;
  actions_1_1_0.lsra_fastsend = actions_1_0_0->lsra_fastsend;

  actions_1_1_0.lsra_alloc_mem = actions_1_0_0->lsra_alloc_mem;
  actions_1_1_0.lsra_free_mem = actions_1_0_0->lsra_free_mem;

  actions_1_1_0.lsra_checkpoint = actions_1_0_0->lsra_checkpoint;
  actions_1_1_0.lsra_continue = actions_1_0_0->lsra_continue;
  actions_1_1_0.lsra_restart = actions_1_0_0->lsra_restart;

  actions_1_1_0.lsra_tv_queue_support =
    actions_1_0_0->lsra_tv_queue_support;


  actions_1_1_0.lsra_interrupt = NULL;


  return &actions_1_1_0;
}
