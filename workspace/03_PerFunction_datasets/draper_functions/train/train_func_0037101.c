draw_cairo_pages(cairo_t * cairo, listOLD * game_ptr)
{
    matchstate msExport;
    static statcontext scTotal;
    moverecord *pmr;
    statcontext *psc = NULL;
    listOLD *pl;
    int iMove = 0;
    int iGame = 0;
    int page;
    listOLD *pl_hint = NULL;

    IniStatcontext(&scTotal);
    updateStatisticsGame(game_ptr);
    pl = game_ptr->plNext;
    pmr = pl->p;
    FixMatchState(&msExport, pmr);
    ApplyMoveRecord(&msExport, game_ptr, pmr);
    g_assert(pmr->mt == MOVE_GAMEINFO);
    msExport.gs = GAME_PLAYING;
    psc = &pmr->g.sc;
    AddStatcontext(psc, &scTotal);
    iGame = getGameNumber(game_ptr);
    if (game_is_last(plGame))
        pl_hint = game_add_pmr_hint(game_ptr);
    for (pl = pl->plNext, page = 1; pl != game_ptr; pl = pl->plNext, page++) {
        export_boards(pl->p, &msExport, &iMove, iGame, cairo, SIZE_2PERPAGE);
        if (page % 2) {
            cairo_translate(cairo, 0, SIMPLE_BOARD_HEIGHT / 2.0);
        } else {
            cairo_translate(cairo, 0, -SIMPLE_BOARD_HEIGHT / 2.0);
            cairo_show_page(cairo);
        }
    }
    if (!(page % 2)) {
        cairo_translate(cairo, 0, -SIMPLE_BOARD_HEIGHT / 2.0);
        cairo_show_page(cairo);
    }
    if (pl_hint)
        game_remove_pmr_hint(pl_hint);
    return 1;
}
