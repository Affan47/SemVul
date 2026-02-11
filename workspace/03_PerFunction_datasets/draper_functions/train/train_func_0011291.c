e_user_homedir_get(void)
{
   char *d;

   if (_e_user_homedir)
     return _e_user_homedir;

   _e_user_homedir = d = getenv("HOME");
   if (!_e_user_homedir)
     {
	_e_user_homedir = "/tmp";
	_e_user_homedir_len = sizeof("/tmp") - 1;
	return _e_user_homedir;
     }

   _e_user_homedir_len = strlen(_e_user_homedir);
   while ((_e_user_homedir_len > 1) &&
	  (d[_e_user_homedir_len - 1] == '/'))
     {
	_e_user_homedir_len--;
	d[_e_user_homedir_len] = '\0';
     }
   return _e_user_homedir;
}
