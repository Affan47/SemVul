show_conduct(int final)
{
    char buf[BUFSZ];
    int ngenocided;


    en_win = create_nhwindow(NHW_MENU);
    putstr(en_win, 0, "Voluntary challenges:");
    putstr(en_win, 0, "");

    if (!u.uconduct.food) enl_msg(You_, "have gone", "went", " without food");

    else if (!u.uconduct.unvegan)
    {
        you_have_X("followed a strict vegan diet");
    }
    else if (!u.uconduct.unvegetarian)
    {
        you_have_been("vegetarian");
    }

    if (!u.uconduct.gnostic)
    {
        you_have_been("an atheist");
    }

    if (!u.uconduct.weaphit)
    {
        you_have_never("hit with a wielded weapon");
    }
#ifdef WIZARD
    else if (wizard)
    {
        sprintf(buf, "used a wielded weapon %ld time%s",
                u.uconduct.weaphit, plur(u.uconduct.weaphit));
        you_have_X(buf);
    }
#endif
    if (!u.uconduct.killer)
    {
        you_have_been("a pacifist");
    }

    if (!u.uconduct.literate)
    {
        you_have_been("illiterate");
    }
#ifdef WIZARD
    else if (wizard)
    {
        sprintf(buf, "read items or engraved %ld time%s",
                u.uconduct.literate, plur(u.uconduct.literate));
        you_have_X(buf);
    }
#endif

    ngenocided = num_genocides();
    if (ngenocided == 0)
    {
        you_have_never("genocided any monsters");
    }
    else
    {
        sprintf(buf, "genocided %d type%s of monster%s",
                ngenocided, plur(ngenocided), plur(ngenocided));
        you_have_X(buf);
    }

    if (!u.uconduct.polypiles)
    {
        you_have_never("polymorphed an object");
    }
#ifdef WIZARD
    else if (wizard)
    {
        sprintf(buf, "polymorphed %ld item%s",
                u.uconduct.polypiles, plur(u.uconduct.polypiles));
        you_have_X(buf);
    }
#endif

    if (!u.uconduct.polyselfs)
    {
        you_have_never("changed form");
    }
#ifdef WIZARD
    else if (wizard)
    {
        sprintf(buf, "changed form %ld time%s",
                u.uconduct.polyselfs, plur(u.uconduct.polyselfs));
        you_have_X(buf);
    }
#endif

    if (!u.uconduct.wishes)
    {
        you_have_X("used no wishes");
    }
    else
    {
        sprintf(buf, "used %ld wish%s",
                u.uconduct.wishes, (u.uconduct.wishes > 1L) ? "es" : "");
        you_have_X(buf);

        if (!u.uconduct.wisharti) enl_msg(You_, "have not wished", "did not wish",
                                          " for any artifacts");
    }


    display_nhwindow(en_win, true);
    destroy_nhwindow(en_win);
}
