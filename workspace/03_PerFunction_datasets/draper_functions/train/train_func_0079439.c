_pulse_info_get(Pulse *d __UNUSED__, int type __UNUSED__, Pulse_Server_Info *ev)
{
   Eina_List *l;
   Pulse_Sink *sink;

   pulse_server_info_free(info);
   info = ev;
   EINA_LIST_FOREACH(sinks, l, sink)
     if (ev->default_sink == pulse_sink_name_get(sink))
       {
          if (default_sink == sink) return;
          default_sink = sink;
          if (!_mixer_using_default) e_mod_mixer_pulse_update();
          break;
       }
   e_mod_mixer_pulse_ready(EINA_TRUE);
}
