boxaSelectByArea(BOXA     *boxas,
                 l_int32   area,
                 l_int32   relation,
                 l_int32  *pchanged)
{
BOXA  *boxad;
NUMA  *na;

    PROCNAME("boxaSelectByArea");

    if (!boxas)
        return (BOXA *)ERROR_PTR("boxas not defined", procName, NULL);
    if (relation != L_SELECT_IF_LT && relation != L_SELECT_IF_GT &&
        relation != L_SELECT_IF_LTE && relation != L_SELECT_IF_GTE)
        return (BOXA *)ERROR_PTR("invalid relation", procName, NULL);
    if (pchanged) *pchanged = FALSE;


    na = boxaMakeAreaIndicator(boxas, area, relation);


    boxad = boxaSelectWithIndicator(boxas, na, pchanged);

    numaDestroy(&na);
    return boxad;
}
