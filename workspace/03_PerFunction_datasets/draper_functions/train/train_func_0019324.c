searchDrawingAttrsFor (
        drawAttrs_t * pDA_list,
        float penWidth,
        float penHeight,
        unsigned int color,
        unsigned short flags
        )
{
    drawAttrs_t * curDA = pDA_list;
    while (curDA
           && (abs(penWidth - curDA->penWidth) > 0.3
            || abs(penHeight - curDA->penHeight) > 0.3
            || color != curDA->color
            || flags != curDA->flags))
    {
        curDA = curDA->next;
    }
    return curDA;
}
