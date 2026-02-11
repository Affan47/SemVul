gst_fft_f64_inverse_fft (GstFFTF64 * self, const GstFFTF64Complex * freqdata,
    gdouble * timedata)
{
  g_return_if_fail (self);
  g_return_if_fail (self->inverse);
  g_return_if_fail (timedata);
  g_return_if_fail (freqdata);

  kiss_fftri_f64 (self->cfg, (kiss_fft_f64_cpx *) freqdata, timedata);
}
