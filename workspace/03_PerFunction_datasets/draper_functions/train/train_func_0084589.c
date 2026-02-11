image_glom_ev_job_finished(EvJob* job, void* user_data)
{
  g_assert(job);

  ImageGlom* self = (ImageGlom*)user_data;
  g_assert(self);

  self->on_ev_job_finished(job);
}
