icon(const QString &name) const
{
	if (!iconsets_)
		return 0;

	const PsiIcon *i = 0;
	Iconset *iconset;
	foreach (iconset, *iconsets_) {
		if ( iconset )
			i = iconset->icon(name);

		if ( i )
			break;
	}
	return i;
}
