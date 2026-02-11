get_prev_hist(HISTORY_S *history, char *savethis, unsigned saveflags, void *cntxt)
{
    int nextcurindex;
    size_t l;

    if(!(history && history->histsize > 0))
      return NULL;

    nextcurindex = (history->curindex + 1) % history->histsize;


    if(nextcurindex == history->origindex
       || !(history->hist[nextcurindex] && history->hist[nextcurindex]->str
            && history->hist[nextcurindex]->str[0]))
      return NULL;


    if(history->curindex == history->origindex){
	if(!savethis)
	  savethis = "";

	if(!history->hist[history->origindex]){
	    history->hist[history->origindex] = (ONE_HIST_S *) fs_get(sizeof(ONE_HIST_S));
	    memset(history->hist[history->origindex], 0, sizeof(ONE_HIST_S));
	}

	if(history->hist[history->origindex]->str){
	    if(strlen(history->hist[history->origindex]->str) < (l=strlen(savethis)))
	      fs_resize((void **) &history->hist[history->origindex]->str, l+1);

	    strncpy(history->hist[history->origindex]->str, savethis, l+1);
	    history->hist[history->origindex]->str[l] = '\0';
	}
	else
	  history->hist[history->origindex]->str = cpystr(savethis);

	history->hist[history->origindex]->flags = saveflags;

	history->hist[history->origindex]->cntxt = cntxt;
    }

    history->curindex = nextcurindex;

    return((history->hist[history->curindex] && history->hist[history->curindex]->str)
           ? history->hist[history->curindex]->str : NULL);
}
