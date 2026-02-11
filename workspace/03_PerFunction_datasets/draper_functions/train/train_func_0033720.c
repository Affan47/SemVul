dc_load_sound(int script, int* yield, int* preturnint,
		   char* wav_file, int sound_index)
{
  if (sound_on)
    {
      log_info("getting %s..", wav_file);
      CreateBufferFromWaveFile(wav_file, sound_index);
    }
}
