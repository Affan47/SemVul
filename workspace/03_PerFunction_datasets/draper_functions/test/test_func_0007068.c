makevisual(VisInfo *vi)
{
    if (!allocoutobj(&vi->oo))
	return NULL;

    if (!nextoutobj(&vi->oo, vi->oi.root, &vi->oi.policy))
	return NULL;

    if (!_dxfNormalsObject((Object)vi->oo.g, "connections"))
	return NULL;

    return (Object) vi->oo.g;
}
