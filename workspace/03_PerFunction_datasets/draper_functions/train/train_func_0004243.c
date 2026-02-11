beginAppend(
									     int n_chars_, char *cset_, int bytes_per_char_)
{
  MSTextEditorTypes::Snip *t;
  unsigned long fontinfo = (unsigned long)fontSelectInfo(_mode);

  int n = n_chars_ * bytes_per_char_;
  if (_used+n > _size || (_head && _head->character_set != cset_) ||
      fontinfo != _fontinfo)
   {
     flushAppend();
     if (_size < n)
      {

	_head = derefDataHeader(_head);
	_size = n > HEAD_MIN_SIZE ? n : HEAD_MIN_SIZE;
	_head = (MSTextEditorTypes::SnipData *)
	calloc(1, OffsetOf(MSTextEditorTypes::SnipData, s[0]) + _size);
	_head->refs = 1;
      }
     _fontinfo = fontinfo;
     _head->bytes = bytes_per_char_;
     _head->font = NULL;
     _head->character_set = cset_;
     t = _first = appendSnip();
     t->content.head = _head;
     t->data = &_head->s[_used];
     _head->refs += 1;
   }
  else
  if ((t = _last) == NULL ||  t->content.head != _head ||
      t->space || t->endseq || t->brk || !IsSameMode(t->mode, _mode))
   {
     t = appendSnip();
     t->content.head = _head;
     t->data = &_head->s[_used];
     _head->refs += 1;
   }
  _used += n;
  t->valid = MSFalse;
  return t;
}
