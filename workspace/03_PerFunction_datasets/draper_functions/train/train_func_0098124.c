MakeWordFreqList()
{

	struct wcount *whashtab[N_HASH_DICT];
	wcount **w_list;
	int ix;
	int j;
	int hash;
	wcount *p;
	FILE *f_out;
	char buf[200];
	char buf2[200];

	wxString dir = wxDirSelector(_T("Directory of text files"),path_speaktext);
	if(dir.IsEmpty()) return;

	memset(whashtab,0,sizeof(whashtab));

	wxString path = wxFindFirstFile(dir+_T("/*"),wxFILE);

	while (!path.empty())
	{
		if(path.AfterLast(PATHSEP) != _T("!wordcounts"))
		{
			CountWordFreq(path,whashtab);
			path = wxFindNextFile();
		}
	}


	w_list = (wcount **)malloc(sizeof(wcount *) * n_words);

	ix = 0;
	for(hash=0; hash < N_HASH_DICT; hash++)
	{
		p = whashtab[hash];
		while((p != NULL) && (ix < n_words))
		{
			w_list[ix++] = p;
			p = p->link;
		}
	}

	qsort((void *)w_list,ix,sizeof(wcount *),(int(*)(const void *,const void *))wfreq_sorter);


	strcpy(buf,dir.mb_str(wxConvLocal));
	sprintf(buf2,"%s/!wordcounts",buf);
	if((f_out = fopen(buf2,"w")) == NULL)
		return;

	for(j=0; j<ix; j++)
	{
		p = w_list[j];
		fprintf(f_out,"%5d  %s\n",p->count,p->word);
		free(p);
	}
	fclose(f_out);

}
