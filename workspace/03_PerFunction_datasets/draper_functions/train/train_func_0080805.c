test_emit() const {

  std::list<ListItem> local_list;
  {
    Thread::Mutex::Lock lock(mutex);
    if (emission_list.empty()) return false;
    local_list = emission_list;
  }


  struct EmitItem {
    static void exec(const ListItem& l) {if (!l.blocked) (l.f1)();}
  };
  std::for_each(local_list.begin(), local_list.end(),
		EmitItem::exec);

  return true;
}
