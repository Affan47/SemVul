con_reject(S5BConnection *c)
{
	d->ps->respondError(c->d->peer, c->d->req.id, 406, "Not acceptable");
}
