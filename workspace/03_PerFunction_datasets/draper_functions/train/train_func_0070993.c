get_condition(pTHX)
{
    SV **pc = hv_fetch(Pending_conditionals, get_key(PL_op), KEY_SZ, 0);

    if (pc && SvROK(*pc))
    {
        dSP;
        NDEB(D(L, "get_condition from %p, %p: %p (%s)\n",
                  PL_op, (void *)PL_op->op_targ, pc, hex_key(get_key(PL_op))));

        NDEB(svdump(Pending_conditionals));
        add_condition(aTHX_ *pc, SvTRUE(TOPs) ? 2 : 1);
    }
    else
    {
        PDEB(D(L, "All is lost, I know not where to go from %p, %p: %p (%s)\n",
                  PL_op, (void *)PL_op->op_targ, pc, hex_key(get_key(PL_op))));
        dump_conditions(aTHX);
        NDEB(svdump(Pending_conditionals));

        exit(1);
    }

    return PL_op;
}
