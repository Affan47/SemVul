init_defines( void)


{
    int     n = sizeof preset / sizeof (PRESET);
    int     nargs;
    PRESET *    pp;


    nargs = DEF_NOARGS_PREDEF_OLD;
    for (pp = preset; pp < preset + n; pp++) {
        if (pp->name && *(pp->name))
            look_and_install( pp->name, nargs, null, pp->val);
        else if (! pp->name)
            nargs = DEF_NOARGS_PREDEF;
    }

    look_and_install( "__MCPP", DEF_NOARGS_PREDEF, null, "2");


}
