es_joystick_eventState(sdl_data *sd, int len,char *buff)
{
   int sendlen;
   char *bp, *start;
   int state;

   bp = buff;
   state = get32be(bp);
   bp = start = sdl_get_temp_buff(sd, 4);
   state = SDL_JoystickEventState(state);
   put32be(bp, state);
   sendlen = bp - start;
   sdl_send(sd, sendlen);
}
