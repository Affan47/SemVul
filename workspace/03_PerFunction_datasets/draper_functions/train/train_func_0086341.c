init_perinterp(pTHX)
{
    INIT_STCXT;

    cxt->netorder = 0;
    cxt->forgive_me = -1;
    cxt->accept_future_minor = -1;
}
