balls_hide()
{
    ListEntry *entry = game->balls->head->next;
    Ball *ball;
    int bx, by, bw, bh;
    while ( entry != game->balls->tail ) {
        ball = (Ball*)entry->item;
        entry = entry->next;

        bx = ball->x; by = ball->y;
        bw = ball_w + shadow_size;
        bh = ball_h + shadow_size;
        if (ball->attached) {
            bx += ball->paddle->x;
            by += ball->paddle->y;
        }

        stk_surface_blit( offscreen,
            bx, by, bw,bh,
            stk_display, bx, by );
        stk_display_store_drect();
    }
}
