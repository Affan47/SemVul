uninit_audio()
{
   audio_connection.disconnect();

   if (audio_fd != -1)
   {
      ::close(audio_fd);
      audio_fd = -1;
   }
}
