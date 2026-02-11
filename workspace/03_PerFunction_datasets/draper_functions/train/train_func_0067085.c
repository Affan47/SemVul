es_wm_toggleFullScreen2(ErlDrvPort port, ErlDrvTermData caller, char *buff)
{
    char *bp;
    SDL_Surface *sptr;
    int res;
    ErlDrvTermData rt[8];

    bp = buff;
    POPGLPTR(sptr, bp);
    res = SDL_WM_ToggleFullScreen(sptr);
    rt[0] = ERL_DRV_ATOM; rt[1]=driver_mk_atom((char *) "_esdl_result_");
    rt[2] = ERL_DRV_INT; rt[3] = res;
    rt[4] = ERL_DRV_TUPLE; rt[5] = 2;
    driver_send_term(port,caller,rt,6);
}
