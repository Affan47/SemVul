_basic_apply(E_Config_Dialog *dialog, E_Config_Dialog_Data *cfdata)
{
   E_Mixer_Gadget_Config *conf = dialog->data;
   const char *card, *channel;

   conf->lock_sliders = cfdata->lock_sliders;
   conf->show_locked = cfdata->show_locked;
   conf->keybindings_popup = cfdata->keybindings_popup;
   conf->using_default = EINA_FALSE;

   card = eina_list_nth(cfdata->cards, cfdata->card_num);
   if (card)
     {
        eina_stringshare_del(conf->card);
        conf->card = eina_stringshare_ref(card);
     }

   channel = eina_list_nth(cfdata->channels_names, cfdata->channel);
   if (channel)
     {
        eina_stringshare_del(conf->channel_name);
        conf->channel_name = eina_stringshare_ref(channel);
     }

   e_mixer_update(conf->instance);
   return 1;
}
