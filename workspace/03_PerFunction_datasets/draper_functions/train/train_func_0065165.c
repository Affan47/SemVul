start_stream()
{
  PaError err;
  SHOW_TIME("start_stream");

  my_stream_could_start=0;
  mInCallbackFinishedState = false;

  err = Pa_StartStream(pa_stream);
  SHOW("start_stream > Pa_StartStream=%d (%s)\n", err, Pa_GetErrorText(err));

#if USE_PORTAUDIO == 19
  if(err == paStreamIsNotStopped)
    {
      SHOW_TIME("start_stream > restart stream (begin)");

      err = Pa_StopStream(pa_stream);
      SHOW("start_stream > Pa_StopStream=%d (%s)\n", err, Pa_GetErrorText(err));
      err = Pa_StartStream(pa_stream);
      SHOW("start_stream > Pa_StartStream=%d (%s)\n", err, Pa_GetErrorText(err));
      SHOW_TIME("start_stream > restart stream (end)");
    }
#endif
}
