ecore_con_server_connected_get(Ecore_Con_Server *svr)
{
   if (!ECORE_MAGIC_CHECK(svr, ECORE_MAGIC_CON_SERVER))
     {
        ECORE_MAGIC_FAIL(svr, ECORE_MAGIC_CON_SERVER, "ecore_con_server_connected_get");
        return EINA_FALSE;
     }

   if (svr->connecting)
     return EINA_FALSE;

   return EINA_TRUE;
}
