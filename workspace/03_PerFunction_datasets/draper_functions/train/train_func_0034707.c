set_EFF(void)
{
    register unsigned *row;
    register int symbol;
    register short *sp;
    register int rowsize;
    register int i;
    register int rule;

    rowsize = WORDSIZE(nvars);
    EFF = NEW2(nvars * rowsize, unsigned);

    row = EFF;
    for (i = start_symbol; i < nsyms; i++)
    {
        sp = derives[i];
        for (rule = *sp; rule > 0; rule = *++sp)
        {
            symbol = ritem[rrhs[rule]];
            if (ISVAR(symbol))
            {
                symbol -= start_symbol;
                SETBIT(row, symbol);
            }
        }
        row += rowsize;
    }

    reflexive_transitive_closure(EFF, nvars);

#ifdef        DEBUG
    print_EFF();
#endif
}
