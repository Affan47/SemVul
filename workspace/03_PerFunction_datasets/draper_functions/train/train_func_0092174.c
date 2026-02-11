findEntry(const QString &nick)
{
	for (Q3ListViewItem *j = firstChild(); j; j = j->nextSibling())
		for(Q3ListViewItem *lvi = j->firstChild(); lvi; lvi = lvi->nextSibling()) {
			if(lvi->text(0) == nick)
				return lvi;
		}
	return 0;
}
