_mixer_popup_cb_mute_change(void *data, Evas_Object *obj, void *event __UNUSED__)
{
   E_Mixer_Instance *inst = data;
   E_Mixer_Channel_State *state = &inst->mixer_state;

   state->mute = e_widget_check_checked_get(obj);
   e_mod_mixer_mute_set(inst->sys, inst->channel, state->mute);

   if (!_mixer_using_default) _mixer_gadget_update(inst);
}
