headerClicked(int c)
{
  CLISTVIEW *_object = (CLISTVIEW *)CWidget::get((QObject *)sender());

  if (_object->sorted == c)
    _object->asc = !_object->asc;
  else
    _object->asc = true;

  _object->sorted = c;


}
