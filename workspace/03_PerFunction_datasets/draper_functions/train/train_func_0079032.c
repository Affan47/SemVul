es_waitEvent(sdl_data *sd, int len,char *buff)
{
    if(sd->use_smp)
	gl_dispatch(sd, SDL_WaitEventFunc, len, buff);
    else
	es_waitEvent2(sd->driver_data, driver_caller(sd->driver_data));
}
