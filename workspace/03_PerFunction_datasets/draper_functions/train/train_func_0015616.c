jbRankHausInit(l_int32    components,
               l_int32    maxwidth,
               l_int32    maxheight,
               l_int32    size,
               l_float32  rank)
{
JBCLASSER  *classer;

    PROCNAME("jbRankHausInit");

    if (components != JB_CONN_COMPS && components != JB_CHARACTERS &&
        components != JB_WORDS)
        return (JBCLASSER *)ERROR_PTR("invalid components", procName, NULL);
    if (size < 1 || size > 10)
        return (JBCLASSER *)ERROR_PTR("size not reasonable", procName, NULL);
    if (rank < 0.5 || rank > 1.0)
        return (JBCLASSER *)ERROR_PTR("rank not in [0.5-1.0]", procName, NULL);
    if (maxwidth == 0) {
        if (components == JB_CONN_COMPS)
            maxwidth = MAX_CONN_COMP_WIDTH;
        else if (components == JB_CHARACTERS)
            maxwidth = MAX_CHAR_COMP_WIDTH;
        else
            maxwidth = MAX_WORD_COMP_WIDTH;
    }
    if (maxheight == 0)
        maxheight = MAX_COMP_HEIGHT;

    if ((classer = jbClasserCreate(JB_RANKHAUS, components)) == NULL)
        return (JBCLASSER *)ERROR_PTR("classer not made", procName, NULL);
    classer->maxwidth = maxwidth;
    classer->maxheight = maxheight;
    classer->sizehaus = size;
    classer->rankhaus = rank;
    classer->nahash = numaHashCreate(5507, 4);
    return classer;
}
