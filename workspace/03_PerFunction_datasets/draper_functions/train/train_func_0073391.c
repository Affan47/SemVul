select(TraceFunction* f)
{
  if (!_current) {
    Stack* s = new Stack(f);
    _current = new HistoryItem(s, f);
  }
  else if (_current->function() != f) {

    HistoryItem* item = _current;
    if (item->next()) {
      item = item->next();
      item->last()->setNext(0);

      while (item->next()) {
        item = item->next();
        delete item->last();
      }
      delete item;
    }

    Stack* s = _current->stack();
    if (!s->contains(f)) {
      s = s->split(f);
      if (!s)
        s = new Stack(f);
    }

    item = _current;
    _current = new HistoryItem(s, f);
    item->setNext(_current);
    _current->setLast(item);
  }


  return _current;
}
