our_ldap_set_lderrno(LDAP *ld, int e, char *m, char *s)
{
    int ret;

#if (LDAPAPI >= 2000)
    if(ldap_set_option(ld, LDAP_OPT_ERROR_NUMBER, (void *)&e) == 0)
      ret = LDAP_SUCCESS;
    else
      (void)ldap_get_option(ld, LDAP_OPT_ERROR_NUMBER, (void *)&ret);
#elif (LDAPAPI >= 15)
    ret = ldap_set_lderrno(ld, e, m, s);
#else

    ld->ld_errno = e;
    ret = LDAP_SUCCESS;
#endif

    return(ret);
}
