adjustLastPointer(MSTextEditorTypes::Snip *r)
{
  if (r)
   {
     r->valid = MSFalse;
     do
      {
	if (r->back == _list) { r = NULL; break; }
	r = r->previous();
	r->valid = MSFalse;
      } while (!r->hasEditableContents());
   }
  _last = r;
}
