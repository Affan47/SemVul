SaveAttr(struct attrStack **asp)
{
    struct attrStack *tmp;

    tmp = (struct attrStack *)malloc(sizeof(struct attrStack));
    if (!asp) {
	if (saveAttr) tmp->prev = saveAttr;
	else tmp->prev = NULL;
	saveAttr = tmp;
    } else *asp = tmp;
    tmp->x = con.x;
    tmp->y = con.y;
    tmp->attr = con.attr;
    tmp->fcol = con.fcol;
    tmp->bcol = con.bcol;
}
