linkyformat(MMIOT *f, Cstring text, int image, Footnote *ref)
{
    linkytype *tag;

    if ( image )
	tag = &imaget;
    else if ( tag = pseudo(ref->link) ) {
	if ( f->flags & (NO_PSEUDO_PROTO|SAFELINK) )
	    return 0;
    }
    else if ( (f->flags & SAFELINK) && T(ref->link)
				    && (T(ref->link)[0] != '/')
				    && !isautoprefix(T(ref->link), S(ref->link)) )


	return 0;
    else
	tag = &linkt;

    if ( f->flags & tag->flags )
	return 0;

    if ( tag->link_pfx ) {
	printlinkyref(f, tag, T(ref->link), S(ref->link));

	if ( tag->WxH ) {
	    if ( ref->height ) Qprintf(f," height=\"%d\"", ref->height);
	    if ( ref->width ) Qprintf(f, " width=\"%d\"", ref->width);
	}

	if ( S(ref->title) ) {
	    Qstring(" title=\"", f);
	    ___mkd_reparse(T(ref->title), S(ref->title), INSIDE_TAG, f);
	    Qchar('"', f);
	}

	Qstring(tag->text_pfx, f);
	___mkd_reparse(T(text), S(text), tag->flags, f);
	Qstring(tag->text_sfx, f);
    }
    else
	Qwrite(T(ref->link) + tag->szpat, S(ref->link) - tag->szpat, f);

    return 1;
}
