havege_create(
  H_PARAMS *params)
{
   H_SETUP    *anchor;
   HOST_CFG   *env;
   H_PTR      h = 0;
   H_UINT     n = params->nCores;
   H_UINT     sz = params->ioSz;

   if (0 == n)
      n = 1;
   if (0 == sz)
      sz = DEFAULT_BUFSZ;
   anchor = (H_SETUP *)calloc(sizeof(H_SETUP),1);
   if (NULL==anchor)
      return h;
   h   = &anchor->info;
   h->print_msg = params->msg_out==0? havege_mute : params->msg_out;
   h->metering  = params->metering;
   env = &anchor->cfg;
   havege_tune(env, params);
   h->error           = H_NOERR;
   h->arch            = ARCH;
   h->inject          = params->injection;
   h->n_cores         = n;
   h->havege_opts     = params->options;
   h->i_collectSz     = params->collectSize==0? NDSIZECOLLECT : params->collectSize;
   h->i_readSz        = sz;
   h->tuneData        = env;
   h->cpu             = &env->cpus[env->a_cpu];
   h->instCache       = &env->caches[env->i_tune];
   h->dataCache       = &env->caches[env->d_tune];
#ifdef ONLINE_TESTS_ENABLE
   h->testData = &anchor->std;
   if (havege_test(h, params))
      return h;
#endif
#if NUMBER_CORES>1
   havege_ipc(h, n, sz);
#else
   h->io_buf  = malloc(sz);
   h->threads = NULL;
#endif
   if (NULL==h->io_buf) {
      h->error = H_NOBUF;
      return h;
      }
   havege_ndsetup(h);
   return h;
}
