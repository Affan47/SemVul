__dmp_tskthd(struct task_t *tskp, struct mod_t *mdp)
{
 register int32 i;
 register struct tskthrd_t *ttp;

 if (tskp->tsktyp == FUNCTION)
  {
   if (tskp->tthrds != NULL) __misc_terr(__FILE__, __LINE__);
   return;
  }
 for (i = 0; i < mdp->flatinum; i++)
  {
   if ((ttp = tskp->tthrds[i]) == NULL)
    {
     if (__debug_flg)
      __dbg_msg("*** task %s instance %d has no task threads\n",
       tskp->tsksyp->synam, i);
     continue;
    }
   __cvsim_msg("*** dumping threads for task %s (%s)\n",
    tskp->tsksyp->synam, __msg_blditree(__xs, mdp->moditps[i],
    (struct task_t *) NULL));
   for (; ttp != NULL; ttp = ttp->tthd_r) __dmp_thrd_info(ttp->tthrd);
  }
}
