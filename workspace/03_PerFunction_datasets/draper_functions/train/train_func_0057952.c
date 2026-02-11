toggle_xterm_mouse(int f, int n)
{
#ifndef _WINDOWS
    int e;

    (e=mouseexist()) ? end_mouse() : (void) init_mouse();
    if(e != mouseexist()){
	mouseexist() ? emlwrite(_("Xterm mouse tracking on!"), NULL)
		     : emlwrite(_("Xterm mouse tracking off!"), NULL);
    }
    else if(!e)
      emlwrite(_("Xterm mouse tracking still off ($DISPLAY variable set?)"), NULL);
#endif
    return(TRUE);
}
