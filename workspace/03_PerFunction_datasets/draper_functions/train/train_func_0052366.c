set_design_recursive(QWidget *w, bool set = false)
{
	QObjectList children;
	int i;
	QObject *child;
	CWIDGET *ob = CWidget::getReal(w);

	if (ob)
		set_design_object(ob);

	children = w->children();

	for (i = 0; i < children.count(); i++)
	{
		child = children.at(i);

		if (child->isWidgetType())
			set_design_recursive((QWidget *)child, true);
	}
}
