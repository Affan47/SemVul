mlwrite(UCS *fmt, void *arg)
{
    int   ret, ww;
    UCS   c;
    char *ap;
    COLOR_PAIR *lastc = NULL;


    mlerase();
    movecursor(ttrow, 0);

    if(Pmaster && Pmaster->colors && Pmaster->colors->prcp
       && pico_is_good_colorpair(Pmaster->colors->prcp)){
	lastc = pico_get_cur_color();
	(void) pico_set_colorp(Pmaster->colors->prcp, PSC_NONE);
    }
    else
      (*term.t_rev)(1);

    ap = (char *) &arg;

    while ((c = *fmt++) != 0) {
        if (c != '%') {
	    pputc(c, 1);
	}
        else {
            c = *fmt++;
            switch (c){
	      case 'd':
		mlputi(*(int *)ap, 10);
		ap += sizeof(int);
		break;

	      case 'o':
		mlputi(*(int *)ap,  8);
		ap += sizeof(int);
		break;

	      case 'x':
		mlputi(*(int *)ap, 16);
		ap += sizeof(int);
		break;

	      case 'D':
		mlputli(*(long *)ap, 10);
		ap += sizeof(long);
		break;

	      case 's':
		pputs_utf8(*(char **)ap, 1);
		ap += sizeof(char *);
		break;

              default:
		pputc(c, 1);
		ww = wcellwidth(c);
		ttcol += (ww >= 0 ? ww : 1);
	    }
	}
    }

    ret = ttcol;
    while(ttcol < term.t_ncol)
      pputc(' ', 0);

    movecursor(term.t_nrow - term.t_mrow, ret);

    if(lastc){
	(void) pico_set_colorp(lastc, PSC_NONE);
	free_color_pair(&lastc);
    }
    else
      (*term.t_rev)(0);

    (*term.t_flush)();
    mpresf = TRUE;

    return(ret);
}
