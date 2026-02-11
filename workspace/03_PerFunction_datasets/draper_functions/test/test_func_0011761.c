free_thd_subtree(struct thread_t *thp)
{
 if (thp->thofs != NULL) __free_thd_list(thp->thofs);
 thp->thofscnt = 0;
 thp->thofs = NULL;
 thp->th_fj = FALSE;
}
