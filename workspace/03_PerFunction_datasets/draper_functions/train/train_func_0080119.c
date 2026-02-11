Expand(int required_size) {
  Handle<JSArray> self(this);
  Handle<FixedArray> old_backing(FixedArray::cast(elements()));
  int old_size = old_backing->length();
  int new_size = required_size > old_size ? required_size : old_size;
  Handle<FixedArray> new_backing = Factory::NewFixedArray(new_size);

  for (int i = 0; i < old_size; i++) new_backing->set(i, old_backing->get(i));
  self->SetContent(*new_backing);
}
