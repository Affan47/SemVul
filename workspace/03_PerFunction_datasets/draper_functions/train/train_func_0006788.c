wrap_paragraph(para_data *pdata, word *words,
			   int w, int i1, int i2, paper_conf *conf)
{
    wrappedline *wrapping, *p;
    int spacewidth;
    struct paper_width_ctx ctx;
    int line_height;


    {
	int i;
	line_height = 0;
	for (i = 0; i < NFONTS; i++)
	    if (line_height < pdata->sizes[i])
		line_height = pdata->sizes[i];
	line_height *= UNITS_PER_PT;
    }

    spacewidth = (pdata->sizes[FONT_NORMAL] *
		  string_width(pdata->fonts[FONT_NORMAL], L" ", NULL, 0));
    if (spacewidth == 0) {


	spacewidth = pdata->sizes[FONT_NORMAL] * UNITS_PER_PT / 2;
    }


    ctx.minspacewidth = spacewidth * 3 / 5;
    ctx.pdata = pdata;
    ctx.conf = conf;

    wrapping = wrap_para(words, w - i1, w - i2, paper_width, &ctx, spacewidth);


    pdata->first = pdata->last = NULL;

    for (p = wrapping; p; p = p->next) {
	line_data *ldata;
	word *wd;
	int len, wid, spaces;

	ldata = snew(line_data);

	ldata->pdata = pdata;
	ldata->first = p->begin;
	ldata->end = p->end;
	ldata->line_height = line_height;

	ldata->xpos = (p == wrapping ? i1 : i2);

	if (pdata->last) {
	    pdata->last->next = ldata;
	    ldata->prev = pdata->last;
	} else {
	    pdata->first = ldata;
	    ldata->prev = NULL;
	}
	ldata->next = NULL;
	pdata->last = ldata;

	spaces = 0;
	len = paper_width_list(&ctx, ldata->first, ldata->end, &spaces);
	wid = (p == wrapping ? w - i1 : w - i2);
	wd = ldata->first;

	ldata->hshortfall = wid - len;
	ldata->nspaces = spaces;


	ldata->hshortfall += ctx.minspacewidth * spaces;
	ldata->hshortfall -= spacewidth * spaces;
	ldata->real_shortfall = ldata->hshortfall;


	if (ldata->hshortfall > 0 && !p->next)
	    ldata->hshortfall = 0;

	ldata->aux_text = NULL;
	ldata->aux_text_2 = NULL;
	ldata->aux_left_indent = 0;
	ldata->penalty_before = ldata->penalty_after = 0;
    }

}
