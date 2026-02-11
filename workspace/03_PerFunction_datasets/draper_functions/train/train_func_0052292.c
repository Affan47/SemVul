OnBindingDestroyed(ProxyBinding* binding) {
  BindingList::iterator it =
      std::find(bindings_.begin(), bindings_.end(), binding);
  delete (*it);
  bindings_.erase(it);
}
