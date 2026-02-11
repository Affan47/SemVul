transportStatus(QString name, int s)
{
	PsiIcon *icon = transportStatusPtr(name, s);
	if ( icon )
		return *icon;
	return PsiIcon();
}
