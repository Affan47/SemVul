Perl_regclass_swash(pTHX_ const regexp *prog, const regnode* node, bool doinit, SV** listsvp, SV **altsvp)
{
    PERL_ARGS_ASSERT_REGCLASS_SWASH;

    if (altsvp) {
        *altsvp = NULL;
    }

    return newSVsv(core_regclass_swash(prog, node, doinit, listsvp));
}
