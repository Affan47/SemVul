do_for_all_unused_symbols(Symbol_visitor_base* v) const
{


  for (std::vector<Archive_member>::const_iterator p = this->members_.begin();
       p != this->members_.end();
       ++p)
    {
      Object* obj = p->obj_;
      obj->for_all_global_symbols(p->sd_, v);
    }
}
