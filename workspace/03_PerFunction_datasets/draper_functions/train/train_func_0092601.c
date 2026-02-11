type() const
{
	if(d)
		return d->c->type();
	else
		return QString();
}
