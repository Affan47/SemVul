fl_add_chart_value( FL_OBJECT  * ob,
                    double       val,
                    const char * str,
                    FL_COLOR     col )
{
    FLI_CHART_SPEC *sp = ob->spec;
    int i;

#if FL_DEBUG >= ML_ERR
    if ( ! IsValidClass( ob, FL_CHART ) )
    {
        M_err( "fl_add_chart_value", "%s not a chart", ob ? ob->label : "" );
        return;
    }
#endif


    if ( sp->numb == sp->maxnumb )
    {
        for ( i = 0; i < sp->numb - 1; i++ )
            sp->entries[ i ] = sp->entries[ i + 1 ];
        sp->numb--;
    }


    sp->entries[ sp->numb ].val = val;
    sp->entries[ sp->numb ].col = col;
    sp->entries[ sp->numb ].lcol = sp->lcol;

    if ( str )
        fli_sstrcpy( sp->entries[sp->numb ].str, str, MAX_CHART_LABEL_LEN );
    else
        *sp->entries[sp->numb ].str = '\0';
    sp->numb++;

    fl_redraw_object( ob );
}
