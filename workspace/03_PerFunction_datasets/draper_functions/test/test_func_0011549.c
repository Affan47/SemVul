TuneConnectionAfterFEAT()
{
   if(conn->clnt_supported)
   {
      const char *client=Query("client",hostname);
      if(client && client[0])
      {
	 conn->SendCmd2("CLNT",client);
	 expect->Push(Expect::IGNORE);
      }
   }
   if(conn->lang_supported)
   {
      const char *lang_to_use=Query("lang",hostname);
      if(lang_to_use && lang_to_use[0])
	 conn->SendCmd2("LANG",lang_to_use);
      else
	 conn->SendCmd("LANG");
      expect->Push(Expect::LANG);
   }
   if(conn->utf8_supported && QueryBool("use-utf8",hostname))
   {

      conn->SendCmd("OPTS UTF8 ON");
      expect->Push(Expect::OPTS_UTF8);
   }
   if(conn->host_supported)
   {
      conn->SendCmd2("HOST",hostname);
      expect->Push(Expect::IGNORE);
   }
   if(conn->mlst_attr_supported)
      SendOPTS_MLST();
}
