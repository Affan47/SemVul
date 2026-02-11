vhx_execall (pt_lkdfig)

struct lkdfig *pt_lkdfig;

  {
  struct lkdins *pt_lkdins = pt_lkdfig->LKDINS;

  while (pt_lkdins != NULL)
    {
    VHX_EXECUTE     = addptype (VHX_EXECUTE, 'I', pt_lkdins);
    pt_lkdins->EVAL = '1';
    pt_lkdins       = pt_lkdins->NEXT;
    }
  }
