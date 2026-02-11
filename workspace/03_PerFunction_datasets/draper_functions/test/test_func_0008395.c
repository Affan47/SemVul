TransferObject(Handle<JSObject> from, Handle<JSObject> to) {
  HandleScope outer;

  ASSERT(!from->IsJSArray());
  ASSERT(!to->IsJSArray());

  TransferNamedProperties(from, to);
  TransferIndexedProperties(from, to);


  Handle<Map> old_to_map = Handle<Map>(to->map());
  Handle<Map> new_to_map = Factory::CopyMapDropTransitions(old_to_map);
  new_to_map->set_prototype(from->map()->prototype());
  to->set_map(*new_to_map);
}
