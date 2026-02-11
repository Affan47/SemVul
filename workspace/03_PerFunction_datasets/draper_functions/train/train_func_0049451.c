_pos_selected_cb(void *data __UNUSED__, Evas_Object *obj, void *event_info)
{
   Elm_Actionslider_Pos ipos, mpos, epos;

   printf("Selection: %s\n", (char *)event_info);
   printf("Label selected: %s\n", elm_actionslider_selected_label_get(obj));

   ipos = elm_actionslider_indicator_pos_get(obj);

   switch (ipos)
     {
      case ELM_ACTIONSLIDER_NONE:
         printf("actionslider indicator pos: none!\n");
         break;
      case ELM_ACTIONSLIDER_LEFT:
         printf("actionslider indicator pos: left!\n");
         break;
      case ELM_ACTIONSLIDER_CENTER:
         printf("actionslider indicator pos: center!\n");
         break;
      case ELM_ACTIONSLIDER_RIGHT:
         printf("actionslider indicator pos: right!\n");
         break;
      case ELM_ACTIONSLIDER_ALL:
         printf("actionslider indicator pos: all!\n");
         break;
     }

   mpos = elm_actionslider_magnet_pos_get(obj);

   switch (mpos)
     {
      case ELM_ACTIONSLIDER_NONE:
         printf("actionslider magnet pos: none!\n");
         break;
      case ELM_ACTIONSLIDER_LEFT:
         printf("actionslider magnet pos: left!\n");
         break;
      case ELM_ACTIONSLIDER_CENTER:
         printf("actionslider magnet pos: center!\n");
         break;
      case ELM_ACTIONSLIDER_RIGHT:
         printf("actionslider magnet pos: right!\n");
         break;
      case ELM_ACTIONSLIDER_ALL:
         printf("actionslider magnet pos: all!\n");
         break;
     }

   epos = elm_actionslider_enabled_pos_get(obj);

   if (epos)
     {
        printf("actionslider enabled pos: ");
        if (epos & ELM_ACTIONSLIDER_LEFT)
          printf("left ");
        if (epos & ELM_ACTIONSLIDER_CENTER)
          printf("center ");
        if (epos & ELM_ACTIONSLIDER_RIGHT)
          printf("right ");
        printf("\n");
     }
}
