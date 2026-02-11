on_first()
{
    int change = 0;

    while(game->prev() != -1)
        change = 1;

    if(change)
    {
        game->breakMove();
        game->updateView();
    }
}
