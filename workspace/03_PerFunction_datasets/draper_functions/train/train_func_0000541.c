createTextElement(const QString &ns, const QString &tagName, const QString &text)
{
	QDomElement e = d->s->doc().createElementNS(ns, tagName);
	e.appendChild(d->s->doc().createTextNode(text));
	return e;
}
