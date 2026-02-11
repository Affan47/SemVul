deleteNodeContent()
{
    if (!d) return;
    if (d->pParent) { detachFromParent(d); d->pParent=NULL; d->ref_count--; }
    emptyTheNode(1);
}
