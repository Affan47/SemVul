text_drawaln(struct AbstractTview* tv, int tid, int pos)
    {
    int y,x;
    html_tview_t* ptr=FROM_TV(tv);
    html_clear(tv);
    base_draw_aln(tv,  tid, pos);
    int is_term= isatty(fileno(ptr->out));

    for(y=0;y< ptr->row_count;++y)
    	{
    	for(x=0;x< tv->mcol;++x)
	    	{
	    	if(is_term)
	    		{
	    		int css=0;
	    		while(css<32)
	    			{
	    			if(( (ptr->screen[y][x].attributes) & (1 << (css)))!=0)
	    				{
	    				break;
	    				}
	    			++css;
	    			}
    			switch(css)
    				{

			    	case 1: fputs(ANSI_COLOR_BLUE,ptr->out); break;
				case 2: fputs(ANSI_COLOR_GREEN,ptr->out); break;
				case 3: fputs(ANSI_COLOR_YELLOW,ptr->out); break;

				case 5: fputs(ANSI_COLOR_GREEN,ptr->out); break;
				case 6: fputs(ANSI_COLOR_CYAN,ptr->out); break;
				case 7: fputs(ANSI_COLOR_YELLOW,ptr->out); break;
				case 8: fputs(ANSI_COLOR_RED,ptr->out); break;
				case 9: fputs(ANSI_COLOR_BLUE,ptr->out); break;
				default:break;
    				}
    			if(( (ptr->screen[y][x].attributes) & (1 << (UNDERLINE_FLAG)))!=0)
    				{
    				fputs(ANSI_UNDERLINE_SET,ptr->out);
    				}

	    		}


	    	int ch=ptr->screen[y][x].ch;

	    	fputc(ch,ptr->out);
	    	if(is_term)
	    		{
	    		fputs(ANSI_COLOR_RESET,ptr->out);
	    		if(( (ptr->screen[y][x].attributes) & (1 << (UNDERLINE_FLAG)))!=0)
    				{
    				fputs(ANSI_UNDERLINE_UNSET,ptr->out);
    				}
	    		}
	    	}
    	fputc('\n',ptr->out);
    	}
    return 0;
    }
