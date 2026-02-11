value(const datetime_t& moment)
{
  datetime_t age;
  amount_t   price;

  if (history) {
    assert(history->prices.size() > 0);

    if (! moment) {
      history_map::reverse_iterator r = history->prices.rbegin();
      age   = (*r).first;
      price = (*r).second;
    } else {
      history_map::iterator i = history->prices.lower_bound(moment);
      if (i == history->prices.end()) {
	history_map::reverse_iterator r = history->prices.rbegin();
	age   = (*r).first;
	price = (*r).second;
      } else {
	age = (*i).first;
	if (moment != age) {
	  if (i != history->prices.begin()) {
	    --i;
	    age	  = (*i).first;
	    price = (*i).second;
	  } else {
	    age = 0;
	  }
	} else {
	  price = (*i).second;
	}
      }
    }
  }

  if (updater && ! (flags & COMMODITY_STYLE_NOMARKET))
    (*updater)(*this, moment, age,
	       (history && history->prices.size() > 0 ?
		(*history->prices.rbegin()).first : datetime_t()), price);

  return price;
}
