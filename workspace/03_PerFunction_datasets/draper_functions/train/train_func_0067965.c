addUniqueItem(MprList *list, HttpRouteOp *op)
{
    mprAssert(list);
    mprAssert(op);

    if (!opPresent(list, op)) {
        mprAddItem(list, op);
    }
}
