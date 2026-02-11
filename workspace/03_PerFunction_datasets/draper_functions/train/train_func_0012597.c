xlspdxload(XLabels_t * xlp)
{
    HDict_t *op=0;

    for (op = dtfirst(xlp->hdx); op; op = dtnext(xlp->hdx, op)) {

	RTreeInsert(xlp->spdx, &op->d.rect, op->d.data, &xlp->spdx->root, 0);
    }
    return 0;
}
