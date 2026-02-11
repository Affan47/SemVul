setIcon(const PsiIcon *i, bool _copyIcon)
	{
		copyIcon = _copyIcon;

		stopIcon();
#ifndef WIDGET_PLUGIN
		if ( i && copyIcon )
			icon = new PsiIcon(*i);
		else
			icon = (PsiIcon *)i;
#else
    Q_UNUSED(i);
#endif
		startIcon();
	}
