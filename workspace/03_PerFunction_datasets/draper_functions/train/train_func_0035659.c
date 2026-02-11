doReject(IBBConnection *c, const QString &id,
						  Stanza::Error::ErrorCond cond, const QString &str)
{
	d->ibb->respondError(c->peer(), id, cond, str);
}
