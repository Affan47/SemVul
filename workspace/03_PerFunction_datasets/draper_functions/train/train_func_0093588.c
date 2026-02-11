cleanup()
{
    if ( !color_init )
	return;
    color_init = false;
    int scr;
    for ( scr = 0; scr < screencount; scr++ ) {
	if ( screendata[scr]->g_carr ) {
	    delete [] screendata[scr]->g_carr;
	    screendata[scr]->g_carr = 0;
	}
	if ( screendata[scr]->g_our_alloc ) {
	    delete [] screendata[scr]->g_our_alloc;
	    screendata[scr]->g_our_alloc = 0;
	}
#if 0
	if ( screendata[scr]->colorDict ) {
	    screendata[scr]->colorDict->setAutoDelete( true );
	    screendata[scr]->colorDict->clear();
	    delete screendata[scr]->colorDict;
	    screendata[scr]->colorDict = 0;
	}
#endif
	delete screendata[scr];
	screendata[scr] = 0;
    }
    delete [] screendata;
    screendata = 0;
    screencount = 0;
}
