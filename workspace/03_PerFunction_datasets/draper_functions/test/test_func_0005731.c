ecore_con_server_del(Ecore_Con_Server *svr)
{
   if (!ECORE_MAGIC_CHECK(svr, ECORE_MAGIC_CON_SERVER))
     {
        ECORE_MAGIC_FAIL(svr, ECORE_MAGIC_CON_SERVER, "ecore_con_server_del");
        return NULL;
     }

   if (svr->delete_me)
     return NULL;

   _ecore_con_server_kill(svr);
   return svr->data;
}
