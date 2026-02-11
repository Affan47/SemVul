sge_is_admin_user(const char *username)
{
   bool       ret = false;
   const char *admin_user;
#ifdef INTERIX
   char       fq_name[1024];
#endif

   admin_user = bootstrap_get_admin_user();
   if(admin_user != NULL && username != NULL) {
#ifdef INTERIX


      wl_build_fq_local_name(admin_user, fq_name);
      admin_user = fq_name;
#endif
      ret = strcmp(username, admin_user)==0 ? true : false;
   }

   return ret;
}
