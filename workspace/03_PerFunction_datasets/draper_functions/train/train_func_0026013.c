_e_border_cb_config_mode(void *data    __UNUSED__,
                         int ev_type __UNUSED__,
                         void *ev      __UNUSED__)
{
   Eina_List *l;
   E_Border *bd;


   if (e_config->mode.presentation)
     {
        EINA_LIST_FOREACH(borders, l, bd)
          {
             if ((bd->fullscreen) || (bd->need_fullscreen))
               {
                  bd->fullscreen = 0;
                  e_border_layer_set(bd, E_LAYER_TOP);
                  bd->fullscreen = 1;
               }
          }
     }
   else if (!e_config->allow_above_fullscreen)
     {
        EINA_LIST_FOREACH(borders, l, bd)
          {
             if ((bd->fullscreen) || (bd->need_fullscreen))
               {
                  bd->fullscreen = 0;
                  e_border_layer_set(bd, E_LAYER_FULLSCREEN);
                  bd->fullscreen = 1;
               }
          }
     }
   return ECORE_CALLBACK_PASS_ON;
}
