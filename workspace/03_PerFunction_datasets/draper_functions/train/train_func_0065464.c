two_rot(struct tnode_t *bal_pt, struct tnode_t *bal_down,
 struct tnode_t *balpt_par)
{
 struct tnode_t *tmp;

 if (bal_pt->via_dir == BLEFT)
  {
   tmp = bal_down->rp;
   bal_down->rp = tmp->lp;
   tmp->lp = bal_down;
   bal_pt->lp = tmp->rp;
   tmp->rp = bal_pt;
  }
 else
  {
   tmp = bal_down->lp;
   bal_down->lp = tmp->rp;
   tmp->rp = bal_down;
   bal_pt->rp = tmp->lp;
   tmp->lp = bal_pt;
  }


 if (tmp->bal == BEVEN) bal_pt->bal = bal_down->bal = BEVEN;
 else if (tmp->bal == bal_pt->via_dir)
  {
   if (bal_pt->via_dir == BRIGHT) bal_pt->bal = BLEFT;
   else if (bal_pt->via_dir == BLEFT) bal_pt->bal = BRIGHT;
   else bal_pt->bal = BEVEN;
   bal_down->bal = BEVEN;
  }
 else { bal_pt->bal = BEVEN; bal_down->bal = bal_pt->via_dir; }
 tmp->bal = BEVEN;


 if (balpt_par == NULL) __tmp_head = tmp;
 else if (balpt_par->via_dir == BLEFT) balpt_par->lp = tmp;
 else balpt_par->rp = tmp;
}
