osd_update_audio_stream(INT16 *buffer)
{
   int i, samplerate_buffer_size;

   samplerate_buffer_size = (Machine->sample_rate / Machine->drv->frames_per_second);

   if(stereo)
      memcpy(XsoundBuffer, buffer, samplerate_buffer_size * 4);
   else
   {
      for (i = 0; i < samplerate_buffer_size; i ++)
      {
         XsoundBuffer[i * 2 + 0] = buffer[i];
         XsoundBuffer[i * 2 + 1] = buffer[i];
      }
   }

   return (Machine->sample_rate / Machine->drv->frames_per_second);
}
