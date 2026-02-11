e_mixer_pulse_get_mute(E_Mixer_System *self, E_Mixer_Channel *channel __UNUSED__, int *mute)
{
   if (mute) *mute = pulse_sink_muted_get((void *)self);
   return 1;
}
