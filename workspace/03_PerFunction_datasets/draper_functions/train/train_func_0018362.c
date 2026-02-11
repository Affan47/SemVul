HUlib_eraseSText(hu_stext_t* s)
{

    int i;

    for (i=0 ; i<s->h ; i++)
    {
	if (s->laston && !*s->on)
	    s->l[i].needsupdate = 4;
	HUlib_eraseTextLine(&s->l[i]);
    }
    s->laston = *s->on;

}
