_mixer_sys_setup(E_Mixer_Instance *inst)
{
   E_Mixer_Gadget_Config *conf;

   conf = inst->conf;
   if ((!_mixer_using_default) && (!e_mixer_pulse_ready())) return 1;

   if (!conf->card)
     {
        ERR("conf->card in mixer sys setup is NULL");
        return 1;
     }

   if (inst->sys)
     e_mod_mixer_del(inst->sys);

   inst->sys = e_mod_mixer_new(conf->card);
   if (!inst->sys)
     {
        inst->channel = NULL;
        return 0;
     }

   inst->channel = e_mod_mixer_channel_get_by_name(inst->sys, conf->channel_name);
   return !!inst->channel;
}
