getHeader(const QString &var) const
{
	foreach (const QString &s, d->headerLines) {
		int n = s.indexOf(": ");
		if(n == -1)
			continue;
		QString v = s.mid(0, n);
		if(v.toLower() == var.toLower())
			return s.mid(n+2);
	}
	return "";
}
