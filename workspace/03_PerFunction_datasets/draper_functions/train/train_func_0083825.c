app_select_dinsig (app_t app)
{
  static char const aid[] = { 0xD2, 0x76, 0x00, 0x00, 0x66, 0x01 };
  int slot = app->slot;
  int rc;

  rc = iso7816_select_application (slot, aid, sizeof aid, 0);
  if (!rc)
    {
      app->apptype = "DINSIG";

      app->fnc.learn_status = do_learn_status;
      app->fnc.readcert = do_readcert;
      app->fnc.getattr = NULL;
      app->fnc.setattr = NULL;
      app->fnc.genkey = NULL;
      app->fnc.sign = do_sign;
      app->fnc.auth = NULL;
      app->fnc.decipher = NULL;
      app->fnc.change_pin = NULL ;
      app->fnc.check_pin = NULL;

      app->force_chv1 = 1;
   }

  return rc;
}
