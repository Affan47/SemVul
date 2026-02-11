modsin_pager( xml *node, newstr *sp, newstr *ep, newstr *tp, newstr *lp )
{
	if ( xml_tagexact( node, "start" ) ) {
		newstr_newstrcpy( sp, node->value );
	} else if ( xml_tagexact( node, "end" ) ) {
		newstr_newstrcpy( ep, node->value );
	} else if ( xml_tagexact( node, "total" ) ) {
		newstr_newstrcpy( tp, node->value );
	} else if ( xml_tagexact( node, "list" ) ) {
		newstr_newstrcpy( lp, node->value );
	}
	if ( node->down ) modsin_pager( node->down, sp, ep, tp, lp );
	if ( node->next ) modsin_pager( node->next, sp, ep, tp, lp );
}
