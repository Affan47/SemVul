cmdlifo_update()
{
    char buffer[4096];
    size_t l;
    size_t nb = _cmdlifo_nb;

    if(nb == 0)
        return;
    --nb;

    while((l = spawn_read(_cmdlifo_sps[nb].sp, buffer, 4095)) != 0) {
        buffer[l] = '\0';
        if(!_cmdlifo_parse_buffer(buffer))
            return;
    }

    if(spawn_ended(_cmdlifo_sps[nb].sp))
        cmdlifo_pop();
}
