gst_sim_syn_calculate_buffer_frames(GstBtSimSyn *self) {
  const gdouble ticks_per_minute=(gdouble)(self->beats_per_minute*self->ticks_per_beat);

  self->samples_per_buffer=((self->samplerate*60.0)/ticks_per_minute);
  self->ticktime=(GstClockTime)(0.5+((GST_SECOND*60.0)/ticks_per_minute));
  GST_DEBUG("samples_per_buffer=%lf",self->samples_per_buffer);
}
