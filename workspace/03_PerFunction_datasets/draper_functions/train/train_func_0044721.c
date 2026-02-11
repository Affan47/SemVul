count() const
{
	QObjectList list = widget->children();
	QObject *ob;
	int n = 0;
	int i;

	for(i = 0; i < list.count(); i++)
	{
		ob = list.at(i);
		if (ob->isWidgetType() && CWidget::getRealExisting(ob))
			n++;
	}

	return n;
}
