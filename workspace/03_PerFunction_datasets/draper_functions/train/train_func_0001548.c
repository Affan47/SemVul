pscr(int l, int o)
{
    if((l >= 0 && l <= term.t_nrow) && (o >= 0 && o < term.t_ncol))
      return(&(pscreen[l]->v_text[o]));
    else
      return(NULL);
}
