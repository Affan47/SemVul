mlerase(void)
{
    if (term.t_nrow < term.t_mrow)
      return;

    movecursor(term.t_nrow - term.t_mrow, 0);
    (*term.t_rev)(0);
    if (TERM_EOLEXIST == TRUE)
      peeol();
    else{
	if(ttrow == term.t_nrow){
	  while(ttcol++ < term.t_ncol-1)
	    (*term.t_putchar)(' ');
	}
	else{
	  while(ttcol++ < term.t_ncol)
	    (*term.t_putchar)(' ');
	}
    }

    (*term.t_flush)();
    mpresf = FALSE;
}
