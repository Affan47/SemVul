do_reset_eat(void)
{
#ifdef DEBUG
    debugpline("do_reset_eat...");
#endif
    if (victual.piece)
    {
        victual.piece = touchfood(victual.piece);
        recalc_wt();
    }
    victual.fullwarn = victual.eating = victual.doreset = false;


    stop_occupation();
    newuhs(false);
}
