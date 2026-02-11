get_best_player_hand(game_tp g, int player_id)
{

    card_t last_hand[5];
    card_t cur_hand[5];
    int i;
    int j;
    int k;


    for (i = 0; i < 5; i++)
        last_hand[i] = g->community[i];


    for (i = 0; i < 5; i++) {
         for (j = 0; j < i; j++) {
             for (k = 0; k < 5; k++)
                 cur_hand[k] = g->community[k];
             cur_hand[i] = g->players[player_id].hand[0];
             cur_hand[j] = g->players[player_id].hand[1];


             if (handcmp(cur_hand, last_hand) > 0)
                 for (k = 0; k < 5; k++)
                     last_hand[k] = cur_hand[k];
         }
    }


    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++)
            cur_hand[j] = g->community[j];
        cur_hand[i] = g->players[player_id].hand[0];

        if (handcmp(cur_hand, last_hand) > 0)
            for (j = 0; j < 5; j++)
                last_hand[j] = cur_hand[j];

        for (j = 0; j < 5; j++)
            cur_hand[j] = g->community[j];
        cur_hand[i] = g->players[player_id].hand[1];

        if (handcmp(cur_hand, last_hand) > 0)
            for (j = 0; j < 5; j++)
                last_hand[j] = cur_hand[j];
    }


    for (i = 0; i < 5; i++)
        g->players[player_id].best_hand[i] = last_hand[i];
}
