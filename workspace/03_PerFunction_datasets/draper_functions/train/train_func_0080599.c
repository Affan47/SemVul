_populate_channels(E_Mixer_App_Dialog_Data *app)
{
   Eina_List *l;
   Evas_Object *ilist;
   int header_input;
   int i;

   ilist = app->ui.channels.list;
   edje_freeze();
   e_widget_ilist_freeze(ilist);
   e_widget_ilist_clear(ilist);

   if (app->sys)
     e_mod_mixer_del(app->sys);
   app->sys = e_mod_mixer_new(app->card);
   if (_mixer_using_default)
     e_mixer_system_callback_set(app->sys, _cb_system_update, app);

   eina_stringshare_del(app->channel_name);
   app->channel_name = e_mod_mixer_channel_default_name_get(app->sys);

   if (app->channels_infos)
     _channels_info_free(app->channels_infos);
   app->channels_infos = _channels_info_new(app->sys);

   if (app->channels_infos)
     {
        struct channel_info *info = app->channels_infos->data;
        if (info->has_capture)
          {
             e_widget_ilist_header_append(ilist, NULL, _("Input"));
             header_input = 1;
             i = 1;
          }
        else
          {
             e_widget_ilist_header_append(ilist, NULL, _("Output"));
             header_input = 0;
             i = 1;
          }
     }

   for (l = app->channels_infos; l; l = l->next, i++)
     {
        struct channel_info *info = l->data;

        if ((!header_input) && info->has_capture)
          {
             e_widget_ilist_header_append(ilist, NULL, _("Input"));
             header_input = 1;
             i++;
          }

        info->app = app;
        e_widget_ilist_append(ilist, NULL, info->name, _cb_channel_selected,
                              info, info->name);
        if (app->channel_name && info->name &&
            (strcmp(app->channel_name, info->name) == 0))
          {
             e_widget_ilist_selected_set(ilist, i);
             app->channel_info = info;
          }
     }

   e_widget_ilist_go(ilist);
   e_widget_ilist_thaw(ilist);
   edje_thaw();
}
