setResource(const QString &s)
{
	if(!valid)
		return;
	QString norm;
	if(!validResource(s, norm)) {
		reset();
		return;
	}
	r = norm;
	update();
}
