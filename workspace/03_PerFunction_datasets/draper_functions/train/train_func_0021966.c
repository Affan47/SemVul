handle( int ms )
{
    int        recv_limit;
    ServerUser    *user = 0;
    ServerChannel    *channel = 0;
    ServerGame     *game = 0;

    recv_limit = server_recv_limit;
    while ( net_recv_packet() && ( recv_limit==-1 || recv_limit > 0) ) {

        if ( msg_is_connectionless() ) {
            handle_connectionless_packet();
            continue;
        }


        find_send_user( &user, &channel, &game );
        if ( user == 0 ) continue;


        if ( !socket_process_header( &user->socket ) ) continue;


        if ( game )
            parse_packet_game( game, user );
        else
        if ( channel )
            parse_packet_channel( user, channel );

        if ( recv_limit != -1 ) recv_limit--;
    }

    remove_zombies();

    update_games( ms );
}
