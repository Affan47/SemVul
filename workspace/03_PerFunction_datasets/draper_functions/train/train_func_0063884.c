set_button(CBUTTON *_object, const char *text, bool resize = false)
{
  QPixmap p;
  QString qtext;
  QIcon icon;
  int size;

	size = qMin(WIDGET->width(), WIDGET->height()) - 6;
	if (resize && size == THIS->last_size)
		return;

  if (text == NULL)
  {
    qtext = WIDGET->text();

		if (THIS->picture)
		{
			p = *(THIS->picture->pixmap);


				CWIDGET_iconset(icon, p);
			WIDGET->setIcon(icon);
			WIDGET->setIconSize(p.size());
		}
		else
		{
			WIDGET->setIcon(icon);
		}
  }
  else
  {
    qtext = TO_QSTRING(text);
		WIDGET->setText(qtext);
  }

  WIDGET->calcMinimumSize();
}
