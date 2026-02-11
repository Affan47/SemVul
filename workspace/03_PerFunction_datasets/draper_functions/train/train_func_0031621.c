es_joystick_opened(sdl_data *sd, int len,char *buff)
{
   int sendlen;
   char *bp, *start;
   int index, bool;

   bp = buff;
   index = get8(bp);
   bp = start = sdl_get_temp_buff(sd, 1);
   bool = SDL_JoystickOpened(index);
   put8(bp, bool);
   sendlen = bp - start;
   sdl_send(sd, sendlen);
}
