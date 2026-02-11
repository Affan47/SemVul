NewBind( uAction * action, int player )
{

    for ( int i = SDLK_NEWLAST-1; i >= 0; --i )
    {

        uBind * old = keymap[i];
        if ( old && old->act == action )
        {
            uBindPlayer * oldPlayer = dynamic_cast< uBindPlayer * >( old );
            if ( oldPlayer && oldPlayer->ePlayer == player )
                return oldPlayer;
        }
    }


    return tNEW(uBindPlayer)( action, player );
}
