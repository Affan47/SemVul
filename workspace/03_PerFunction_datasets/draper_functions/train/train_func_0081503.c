add_filter(IndividualFilter * filter)
  {
    Filters::iterator cur, end;
    cur = filters_.begin();
    end = filters_.end();
    while ((cur != end) && (filter->order_num() > (*cur)->order_num())){
      ++cur;
    }
    filters_.insert(cur, filter);
  }
