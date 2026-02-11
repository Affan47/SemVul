containedWidgets() const {
	QStringList tmp;
	for (struct ListItem *it=m_childrenListBegin;it;it=it->next) {
		tmp<<QString(it->data);
	}

	return tmp;
}
