play_wave_sync(cst_wave *w, cst_relation *rel,
		   int (*call_back)(cst_item *))
{
    int q,i,n,r;
    cst_audiodev *ad;
    float r_pos;
    cst_item *item;

    if (!w)
	return CST_ERROR_FORMAT;

    if ((ad = audio_open(w->sample_rate,w->num_channels,
			 CST_AUDIO_LINEAR16)) == NULL)
	return CST_ERROR_FORMAT;

    q=0;
    item = relation_head(rel);
    r_pos = w->sample_rate * 0;
    for (i=0; i < w->num_samples; i += r/2)
    {
	if (i >= r_pos)
	{
	    audio_flush(ad);

	    if ((*call_back)(item) != CST_OK_FORMAT)
		break;
	    item = item_next(item);
	    if (item)
		r_pos = w->sample_rate * val_float(ffeature(item,"p.end"));
	    else
		r_pos = w->num_samples;
	}
	if (w->num_samples > i+CST_AUDIOBUFFSIZE)
	    n = CST_AUDIOBUFFSIZE;
	else
	    n = w->num_samples-i;
	r = audio_write(ad,&w->samples[i],n*2);
	q +=r;
	if (r <= 0)
	    cst_errmsg("failed to write %d samples\n",n);
    }

    audio_close(ad);

    return CST_OK_FORMAT;
}
