forward_ldap_entry(struct pine *ps, LDAP_CHOOSE_S *winning_e)
{
    STORE_S    *srcstore = NULL;
    SourceType  srctype = CharStar;

    dprint((9, "- forward_ldap_entry -\n"));

    if((srcstore = prep_ldap_for_viewing(ps,winning_e,srctype,NULL)) != NULL){
	forward_text(ps, so_text(srcstore), srctype);
	ps->mangled_screen = 1;
	so_give(&srcstore);
    }
    else
      q_status_message(SM_ORDER, 0, 2, _("Error allocating space"));
}
