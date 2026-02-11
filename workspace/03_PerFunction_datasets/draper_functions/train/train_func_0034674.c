boxBoundingRegion(BOX  *box1,
                  BOX  *box2)
{
l_int32  left, top, right1, right2, right, bot1, bot2, bot;

    PROCNAME("boxBoundingRegion");

    if (!box1)
        return (BOX *)ERROR_PTR("box1 not defined", procName, NULL);
    if (!box2)
        return (BOX *)ERROR_PTR("box2 not defined", procName, NULL);

    left = L_MIN(box1->x, box2->x);
    top = L_MIN(box1->y, box2->y);
    right1 = box1->x + box1->w - 1;
    right2 = box2->x + box2->w - 1;
    right = L_MAX(right1, right2);
    bot1 = box1->y + box1->h - 1;
    bot2 = box2->y + box2->h - 1;
    bot = L_MAX(bot1, bot2);
    return boxCreate(left, top, right - left + 1, bot - top + 1);
}
