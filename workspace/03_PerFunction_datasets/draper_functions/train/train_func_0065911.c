subst(const SubstTable<Char> &table, Char space)
{
  for (size_t i = 0; i < items_.size(); i++)
    if (items_[i].type == TextItem::data) {
      size_t lim = (i + 1 < items_.size()
		    ? items_[i + 1].index
		    : chars_.size());
      size_t j;
      for (j = items_[i].index; j < lim; j++) {
	Char c = chars_[j];
	if (c != space && c != table[c])
	  break;
      }
      if (j < lim) {
	size_t start = items_[i].index;
	StringC origChars(chars_.data() + start, lim - start);
	for (; j < lim; j++)
	  if (chars_[j] != space)
	    table.subst(chars_[j]);
	items_[i].loc = Location(new MultiReplacementOrigin(items_[i].loc,
							    origChars),
				 0);
      }
    }
}
