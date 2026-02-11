setEmail(const QString &_text, const QString &_header,
                                  bool _update)
{
  if (_text.isEmpty())
      return;
  d->label[1]->setText(_header);
  d->text[1]->setText(QString("<a href=\"mailto:%1\">%1</a>").arg(_text));
  if (_update) { d->updateLayout(); }
}
