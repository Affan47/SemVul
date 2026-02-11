draw_scores(int xcenter, int y) {
    int n;
    int num_players = 0;

    const client_player_t *sorted[infon->max_players];
    for (n = 0; n < infon->max_players; n++) {
        const client_player_t *player = infon->get_player(n);
        if (!player)
            continue;
        sorted[num_players++] = player;
    }
    qsort(sorted, num_players, sizeof(client_player_t*), player_sort_by_score);

    for (n = 0; n < num_players; n++) {
        const client_player_t *player = sorted[n];
        if (player->num == highlight_player)
            video_draw(xcenter - 48 - 8, y + 14 * n - 8, sprite_get(SPRITE_HALO));
        video_draw(xcenter - 48,
                   y + 14 * n,
                   sprite_get(CREATURE_SPRITE(player->num,
                                              0,
                                              (render_real_time / 60) % CREATURE_DIRECTIONS,
                                              (render_real_time / 123) % 2)));

        static char buf[40];
        snprintf(buf, sizeof(buf), "%2d.     %4d %s", n + 1, player->score, player->name);
        video_write(xcenter - 70,
                    y + 14 * n + 1,
                    buf);
    }
}
