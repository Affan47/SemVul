elm_win_socket_listen(Evas_Object *obj,
                      const char *svcname,
                      int svcnum,
                      Eina_Bool svcsys)
{
   ELM_WIN_CHECK(obj) EINA_FALSE;
   ELM_WIN_DATA_GET_OR_RETURN_VAL(obj, sd, EINA_FALSE);

   if (!sd->ee) return EINA_FALSE;

   if (!ecore_evas_extn_socket_listen(sd->ee, svcname, svcnum, svcsys))
     return EINA_FALSE;

   return EINA_TRUE;
}
