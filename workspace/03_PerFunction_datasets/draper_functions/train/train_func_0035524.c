windows_tot_delete(Private_Repl_Protocol **prpp)
{
	LDAPDebug0Args( LDAP_DEBUG_TRACE, "=> windows_tot_delete\n" );


        if (!(*prpp)->stopped) {
                (*prpp)->stopped = 1;
                (*prpp)->stop(*prpp);
        }

        if ((*prpp)->lock) {
                PR_DestroyLock((*prpp)->lock);
                (*prpp)->lock = NULL;
        }
        if ((*prpp)->cvar) {
                PR_DestroyCondVar((*prpp)->cvar);
                (*prpp)->cvar = NULL;
        }
        slapi_ch_free((void **)&(*prpp)->private);
        slapi_ch_free((void **)prpp);

	LDAPDebug0Args( LDAP_DEBUG_TRACE, "<= windows_tot_delete\n" );
}
