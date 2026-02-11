pputc(UCS c,
      int a)
{
    int ind, width, printable_ascii = 0;


    if((ttcol >= 0 && ttcol < term.t_ncol) && (ttrow >= 0 && ttrow <= term.t_nrow)){


	if(c < 0x80 && isprint(c)){
	    printable_ascii++;
	    width = 1;
	}
	else
	  width = wcellwidth(c);

	if(width < 0)
	  width = 1;

	if(ttcol + width <= term.t_ncol){


	    if(!(ttrow == term.t_nrow && ttcol+width == term.t_ncol)){
		(*term.t_putchar)(c);
		ind = index_from_col(ttrow, ttcol);
		pscreen[ttrow]->v_text[ind].c = c;
		pscreen[ttrow]->v_text[ind].a = a;
	    }
	}
	else{


	}

	ttcol = MIN(term.t_ncol, ttcol+width);
    }
}
