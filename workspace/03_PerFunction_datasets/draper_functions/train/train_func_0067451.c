e_int_config_apps_add(E_Container *con, const char *params __UNUSED__)
{
   E_Desktop_Edit *ed;

   if (!(ed = e_desktop_edit(con, NULL))) return NULL;
   return ed->cfd;
}
