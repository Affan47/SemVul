AllocateGlobalObject(JSFunction* constructor) {
  ASSERT(constructor->has_initial_map());
  Map* map = constructor->initial_map();


  ASSERT(map->NextFreePropertyIndex() == 0);


  ASSERT(map->unused_property_fields() == 0);
  ASSERT(map->inobject_properties() == 0);


  int initial_size = map->instance_type() == JS_GLOBAL_OBJECT_TYPE ? 64 : 512;


  Object* obj;
  { MaybeObject* maybe_obj =
        StringDictionary::Allocate(
            map->NumberOfDescribedProperties() * 2 + initial_size);
    if (!maybe_obj->ToObject(&obj)) return maybe_obj;
  }
  StringDictionary* dictionary = StringDictionary::cast(obj);


  DescriptorArray* descs = map->instance_descriptors();
  for (int i = 0; i < descs->number_of_descriptors(); i++) {
    PropertyDetails details = descs->GetDetails(i);
    ASSERT(details.type() == CALLBACKS);
    PropertyDetails d =
        PropertyDetails(details.attributes(), CALLBACKS, details.index());
    Object* value = descs->GetCallbacksObject(i);
    { MaybeObject* maybe_value = Heap::AllocateJSGlobalPropertyCell(value);
      if (!maybe_value->ToObject(&value)) return maybe_value;
    }

    Object* result;
    { MaybeObject* maybe_result = dictionary->Add(descs->GetKey(i), value, d);
      if (!maybe_result->ToObject(&result)) return maybe_result;
    }
    dictionary = StringDictionary::cast(result);
  }


  { MaybeObject* maybe_obj = Allocate(map, OLD_POINTER_SPACE);
    if (!maybe_obj->ToObject(&obj)) return maybe_obj;
  }
  JSObject* global = JSObject::cast(obj);
  InitializeJSObjectFromMap(global, dictionary, map);


  { MaybeObject* maybe_obj = map->CopyDropDescriptors();
    if (!maybe_obj->ToObject(&obj)) return maybe_obj;
  }
  Map* new_map = Map::cast(obj);


  global->set_map(new_map);
  global->map()->set_instance_descriptors(Heap::empty_descriptor_array());
  global->set_properties(dictionary);


  ASSERT(global->IsGlobalObject());
  ASSERT(!global->HasFastProperties());
  return global;
}
