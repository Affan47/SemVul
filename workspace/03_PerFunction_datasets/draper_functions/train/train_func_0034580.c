body(const QString &lang) const
{
	if (d->body.empty())
		return "";
	else if (d->body.contains(lang))
		return d->body[lang];
	else
		return d->body.begin().value();
}
