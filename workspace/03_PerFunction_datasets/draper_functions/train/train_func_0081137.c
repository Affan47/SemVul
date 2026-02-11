slot_update_hint( int slot_id, Hint *hint )
{
    GameSlot gs;
    int i;
    char text[256], text2[256];
    char *str_diff[] = { "Kids", "Easy", "Medium", "Hard" };

    if ( slot_load( slot_id, &gs ) )
    {
        snprintf( text, 255, "%s - %s, %d Player(s)#",
                  gs.setname, str_diff[gs.diff], gs.player_count );
        for ( i = 0; i < gs.player_count; i++ )
        {
            snprintf( text2, 255, "#%s: %d (Lvl %d)",
                  gs.player_names[i], gs.player_scores[i],
                  gs.player_cur_level_id[i]+1 );
            strcat( text, text2 );
        }
    }
    else
        strcpy( text, "Right now, there is no game you could resume." );
    hint_set_contents( hint, text );
}
