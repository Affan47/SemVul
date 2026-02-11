append(QString n, PsiIcon *icon)
	{

		if ( dict.contains(n) )
			remove(n);

		dict[n] = icon;
		list.append(icon);
	}
