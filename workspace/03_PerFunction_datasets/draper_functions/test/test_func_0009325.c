eject_client(CONNECTION * con)
{
    int  i, loser = -1, leech = 0, shared = 0x7fffffff;
    time_t when = global.current_time;

    for (i = 0; i < global.clients_num; i++)
    {
        if(ISUSER(global.clients[i]) && global.clients[i] != con &&
            !global.clients[i]->killed &&

            check_eject_limits(global.clients[i]->user))
        {


            if(leech && global.clients[i]->user->level > LEVEL_LEECH)
                continue;


            if(leech || (!leech && global.clients[i]->user->level > LEVEL_LEECH))
            {
                if(global.clients[i]->user->shared > shared)
                    continue;
            }

            if(global.clients[i]->user->connected < when)
            {
                loser = i;
                when = global.clients[i]->user->connected;
                if(global.clients[i]->user->level == LEVEL_LEECH)
                    leech = 1;
                shared = global.clients[i]->user->shared;
            }
        }
    }
    if(loser == -1)
        return 0;
    eject_internal(con,global.clients[loser]->user);
    return 1;
}
