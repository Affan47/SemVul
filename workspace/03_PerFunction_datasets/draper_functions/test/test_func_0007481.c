gpredict_help_launch (gpredict_help_type_t type)
{
     browser_type_t idx;
     gint           resp;


     idx = sat_cfg_get_int (SAT_CFG_INT_WEB_BROWSER_TYPE);


     if ((idx < BROWSER_TYPE_NONE) || (idx >= BROWSER_TYPE_NUM)) {
          idx = BROWSER_TYPE_NONE;
     }

     if (idx == BROWSER_TYPE_NONE) {
          sat_log_log (SAT_LOG_LEVEL_MSG,
                    _("%s: Help browser is not set up yet."),
                    __FUNCTION__);

          resp = config_help ();

          if (resp == GTK_RESPONSE_CANCEL) {
               sat_log_log (SAT_LOG_LEVEL_MSG,
                         _("%s: Configure help browser cancelled."),
                         __FUNCTION__);

               return;
          }


          idx = sat_cfg_get_int (SAT_CFG_INT_WEB_BROWSER_TYPE);
     }

     if ((idx <= BROWSER_TYPE_NONE) || (idx >= BROWSER_TYPE_NUM)) {
          return;
     }


     sat_log_log (SAT_LOG_LEVEL_DEBUG,
               _("%s: Launching help browser %s."),
               __FUNCTION__, sat_help[idx].type);

     g_print ("FIXME: FINSH IMPELMTATION\n");
}
