opPresent(MprList *list, HttpRouteOp *op)
{
    HttpRouteOp   *last;

    if ((last = mprGetLastItem(list)) == 0) {
        return 0;
    }
    if (smatch(last->name, op->name) &&
        smatch(last->details, op->details) &&
        smatch(last->var, op->var) &&
        smatch(last->value, op->value) &&
        last->mdata == op->mdata &&
        last->flags == op->flags) {
        return 1;
    }
    return 0;
}
