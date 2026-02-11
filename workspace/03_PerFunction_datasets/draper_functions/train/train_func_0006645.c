view_writec(int c)
{
    static int in_color = 0;

    if(g_view_write->line){


	if(c == '\n' ||
	   (!in_color &&
	    (char)c != TAG_EMBED &&
	    g_view_write->index >= (LINEBUFSIZ - 20 * (RGBLEN+2))) ||
	   (g_view_write->index >= LINEBUFSIZ - 1)){
	    int rv;

	    in_color = 0;
	    suspend_busy_cue();
	    ClearLine(g_view_write->screen_line);
	    if(c != '\n')
	      g_view_write->line[g_view_write->index++] = (char) c;

	    PutLine0n8b(g_view_write->screen_line++, 0,
			g_view_write->line, g_view_write->index,
			g_view_write->handles ? *g_view_write->handles : NULL);

	    resume_busy_cue(0);
	    rv = so_nputs(g_view_write->store,
			  g_view_write->line,
			  g_view_write->index);
	    g_view_write->index = 0;

	    if(g_view_write->screen_line >= g_view_write->last_screen_line){
		fs_give((void **) &g_view_write->line);
		fflush(stdout);
	    }

	    if(!rv)
	      return(0);
	    else if(c != '\n')
	      return(1);
	}
	else{


	    if((char)c == TAG_EMBED)
	      in_color = RGBLEN+1;
	    else if(in_color)
	      in_color--;

	    g_view_write->line[g_view_write->index++] = (char) c;
	    return(1);
	}
    }
#ifdef	_WINDOWS
    else if(c == '\n' && g_view_write->lines++ > SCROLL_LINES(ps_global))
      scroll_setrange(SCROLL_LINES(ps_global),
		      g_view_write->lines + SCROLL_LINES(ps_global));
#endif

    return(so_writec(c, g_view_write->store));
}
