pulse_sink_avg_get_pct(Pulse_Sink *sink)
{
   double avg;
   int x;

   EINA_SAFETY_ON_NULL_RETURN_VAL(sink, -1.0);

   for (avg = 0, x = 0; x < sink->volume.channels; x++)
     avg += sink->volume.values[x];
   avg /= sink->volume.channels;

   if (avg <= PA_VOLUME_MUTED) return 0.0;

   if (avg == PA_VOLUME_NORM) return 100.0;

   return (avg * 100 + PA_VOLUME_NORM / 2) / PA_VOLUME_NORM;
}
