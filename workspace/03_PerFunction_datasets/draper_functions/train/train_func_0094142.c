select_card(E_Mixer_App_Dialog_Data *app)
{
   _populate_channels(app);
   if (e_widget_ilist_count(app->ui.channels.list) > 0)
     e_widget_ilist_selected_set(app->ui.channels.list, 1);
   else
     _disable_channel_editor(app);
}
