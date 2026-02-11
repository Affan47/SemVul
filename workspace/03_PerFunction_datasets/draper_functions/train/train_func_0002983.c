__setup_tsk_thread(struct task_t *tskp)
{
 register struct thread_t *thp;
 register struct tskthrd_t *ttp;


 thp = __alloc_thrd();
 thp->thenbl_sfnam_ind = __sfnam_ind;
 thp->thenbl_slin_cnt = __slin_cnt;


 if (tskp == NULL) __arg_terr(__FILE__, __LINE__);


 if (thp->assoc_tsk != NULL && thp->assoc_tsk != tskp)
  __misc_sgfterr(__FILE__, __LINE__);


 thp->thnxtstp = tskp->tskst;


 ttp = (struct tskthrd_t *) __my_malloc(sizeof(struct tskthrd_t));
 ttp->tthd_l = NULL;
 ttp->tthd_r = tskp->tthrds[__inum];
 tskp->tthrds[__inum] = ttp;
 if (ttp->tthd_r != NULL) ttp->tthd_r->tthd_l = ttp;
 ttp->tthrd = thp;
 thp->assoc_tsk = tskp;

 thp->tthlst = ttp;
 return(thp);
}
