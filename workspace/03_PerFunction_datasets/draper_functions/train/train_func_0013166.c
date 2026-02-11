sam_header_compare_lines(HeaderLine *hline1, HeaderLine *hline2)
{
    HeaderTag *t1, *t2;

    if ( hline1->type[0]!=hline2->type[0] || hline1->type[1]!=hline2->type[1] )
        return 0;

    int itype = tag_exists(hline1->type,types);
    if ( itype==-1 ) {
		debug("[sam_header_compare_lines] Unknown type [%c%c]\n", hline1->type[0],hline1->type[1]);
		return -1;
	}

    if ( unique_tags[itype] )
    {
        t1 = header_line_has_tag(hline1,unique_tags[itype][0]);
        t2 = header_line_has_tag(hline2,unique_tags[itype][0]);
        if ( !t1 || !t2 )
            return 2;

        if ( strcmp(t1->value,t2->value) )
            return 0;
    }
    if ( !required_tags[itype] && !optional_tags[itype] )
    {
        t1 = hline1->tags->data;
        t2 = hline2->tags->data;
        if ( !strcmp(t1->value,t2->value) ) return 1;
        return 0;
    }

    int missing=0, itag=0;
    while ( required_tags[itype] && required_tags[itype][itag] )
    {
        t1 = header_line_has_tag(hline1,required_tags[itype][itag]);
        t2 = header_line_has_tag(hline2,required_tags[itype][itag]);
        if ( !t1 && !t2 )
            return 2;
        else if ( !t1 || !t2 )
            missing = 1;
        else if ( strcmp(t1->value,t2->value) )
        {
            if ( unique_tags[itype] )
                return 2;

            return 0;
        }
        itag++;
    }
    itag = 0;
    while ( optional_tags[itype] && optional_tags[itype][itag] )
    {
        t1 = header_line_has_tag(hline1,optional_tags[itype][itag]);
        t2 = header_line_has_tag(hline2,optional_tags[itype][itag]);
        if ( !t1 && !t2 )
        {
            itag++;
            continue;
        }
        if ( !t1 || !t2 )
            missing = 1;
        else if ( strcmp(t1->value,t2->value) )
        {
            if ( unique_tags[itype] )
                return 2;

            return 0;
        }
        itag++;
    }
    if ( missing ) return 3;
    return 1;
}
