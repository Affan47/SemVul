login_failed_error(MPVIO_EXT *mpvio, int passwd_used)
{
  THD *thd= current_thd;
  if (passwd_used == 2)
  {
    my_error(ER_ACCESS_DENIED_NO_PASSWORD_ERROR, MYF(0),
             mpvio->auth_info.user_name,
             mpvio->auth_info.host_or_ip);
    general_log_print(thd, COM_CONNECT, ER(ER_ACCESS_DENIED_NO_PASSWORD_ERROR),
                      mpvio->auth_info.user_name,
                      mpvio->auth_info.host_or_ip);
#ifndef NO_EMBEDDED_ACCESS_CHECKS
    twitter_audit_logins(thd, COM_CONNECT, (void *)mpvio->acl_user,
                         ER(ER_ACCESS_DENIED_NO_PASSWORD_ERROR),
                         mpvio->auth_info.user_name,
                         mpvio->auth_info.host_or_ip);
#endif


    if (global_system_variables.log_warnings > 1)
    {
      sql_print_warning(ER(ER_ACCESS_DENIED_NO_PASSWORD_ERROR),
                        mpvio->auth_info.user_name,
                        mpvio->auth_info.host_or_ip);
    }
  }
  else
  {
    my_error(ER_ACCESS_DENIED_ERROR, MYF(0),
             mpvio->auth_info.user_name,
             mpvio->auth_info.host_or_ip,
             passwd_used ? ER(ER_YES) : ER(ER_NO));
    general_log_print(thd, COM_CONNECT, ER(ER_ACCESS_DENIED_ERROR),
                      mpvio->auth_info.user_name,
                      mpvio->auth_info.host_or_ip,
                      passwd_used ? ER(ER_YES) : ER(ER_NO));
#ifndef NO_EMBEDDED_ACCESS_CHECKS
    twitter_audit_logins(thd, COM_CONNECT, (void *)mpvio->acl_user,
                         ER(ER_ACCESS_DENIED_ERROR),
                         mpvio->auth_info.user_name,
                         mpvio->auth_info.host_or_ip,
                         passwd_used ? ER(ER_YES) : ER(ER_NO));
#endif


    if (global_system_variables.log_warnings > 1)
    {
      sql_print_warning(ER(ER_ACCESS_DENIED_ERROR),
                        mpvio->auth_info.user_name,
                        mpvio->auth_info.host_or_ip,
                        passwd_used ? ER(ER_YES) : ER(ER_NO));
    }
  }
}
