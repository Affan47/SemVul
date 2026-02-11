Clp_Shift(Clp_Parser *clp, int allow_options)


{
    Clp_ParserState clpsave;
    Clp_SaveParser(clp, &clpsave);
    next_argument(clp, allow_options ? 2 : 1);
    if (!clp->have_val)
	Clp_RestoreParser(clp, &clpsave);
    return clp->vstr;
}
