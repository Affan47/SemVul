es_audioDriverName(sdl_data *sd, int len, char *bp)
{
  int sendlen = 0;

  bp = sdl_get_temp_buff(sd, 256);
  if (SDL_AudioDriverName(bp, 256) != NULL) {
    sendlen = strlen(bp);
  }
  sdl_send(sd, sendlen);
}
