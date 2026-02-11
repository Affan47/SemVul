ldap_next_tmplcol( struct ldap_disptmpl *tmpl, struct ldap_tmplitem *row,
	struct ldap_tmplitem *col )
{
    return( col == NULLTMPLITEM ? col : col->ti_next_in_row );
}
