copy_tskargs(struct task_t *otskp)
{
 register struct task_pin_t *otpp;
 struct task_pin_t *last_ntpp, *ntpp, *ntpp_hdr;

 last_ntpp = NULL;
 ntpp_hdr = NULL;
 for (otpp = otskp->tskpins; otpp != NULL; otpp = otpp->tpnxt)
  {
   ntpp = (struct task_pin_t *) __my_malloc(sizeof(struct task_pin_t));

   *ntpp = *otpp;
   ntpp->tpsy = (struct sy_t *) otpp->tpsy->spltsy;
   ntpp->tpnxt = NULL;
   if (last_ntpp == NULL) ntpp_hdr = ntpp; else last_ntpp->tpnxt = ntpp;
   last_ntpp = ntpp;
  }
 return(ntpp_hdr);
}
