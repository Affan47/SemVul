count_occurrences_1 (rtx *cur_rtx, void *arg)
{
  rtx_search_arg_p p = (rtx_search_arg_p) arg;


  if (exp_equiv_p (*cur_rtx, p->x, 0, true))
    {

      if (REG_P (*cur_rtx)
          && HARD_REGISTER_P (*cur_rtx)
          && hard_regno_nregs[REGNO(*cur_rtx)][GET_MODE (*cur_rtx)] > 1)
        {
          p->n = 0;
          return 1;
        }

      p->n++;


      return -1;
    }

  if (GET_CODE (*cur_rtx) == SUBREG
      && REG_P (p->x)
      && (!REG_P (SUBREG_REG (*cur_rtx))
	  || REGNO (SUBREG_REG (*cur_rtx)) == REGNO (p->x)))
    {


      p->n = 0;
      return 1;
    }


  return 0;
}
