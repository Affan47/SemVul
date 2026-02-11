_mixer_volume_increase(E_Mixer_Instance *inst, Eina_Bool non_ui)
{
   E_Mixer_Channel_State *state;

   state = &inst->mixer_state;
   e_mod_mixer_volume_get(inst->sys, inst->channel,
                          &state->left, &state->right);
   if (state->left >= 0)
     {
        if (state->left < 95)
          state->left += 5;
        else
          state->left = 100;
     }

   if (state->right >= 0)
     {
        if (state->right < 95)
          state->right += 5;
        else
          state->right = 100;
     }

   e_mod_mixer_volume_set(inst->sys, inst->channel,
                          state->left, state->right);
   _mixer_gadget_update(inst);
   if (non_ui)
     _mixer_notify(((float)state->left + (float)state->right) / 2.0, inst);
}
