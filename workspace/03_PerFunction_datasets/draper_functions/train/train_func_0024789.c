InitializeJSObjectFromMap(JSObject* obj,
                                     FixedArray* properties,
                                     Map* map) {
  obj->set_properties(properties);
  obj->initialize_elements();


  Object* filler;


  if (map->constructor()->IsJSFunction() &&
      JSFunction::cast(map->constructor())->shared()->
          IsInobjectSlackTrackingInProgress()) {

    ASSERT(obj->GetInternalFieldCount() == 0);
    filler = Heap::one_pointer_filler_map();
  } else {
    filler = Heap::undefined_value();
  }
  obj->InitializeBody(map->instance_size(), filler);
}
