wcellwidth(UCS ucs)
{
    char dummy[32];
    long w;


    if(native_utf8){
	w = ucs4_width((unsigned long) ucs);
	return((w & U4W_ERROR) ? -1 : w);
    }
    else if(display_data){
	if(wtomb(dummy, ucs) < 0)
	  return(-1);
	else{
	    w = ucs4_width((unsigned long) ucs);
	    return((w & U4W_ERROR) ? -1 : w);
	}
    }
#ifndef _WINDOWS
    else
      return(wcwidth((wchar_t) ucs));
#else
    return(0);
#endif
}
