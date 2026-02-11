AllocateInitialMap(JSFunction* fun) {
  ASSERT(!fun->has_initial_map());


  int instance_size = fun->shared()->CalculateInstanceSize();
  int in_object_properties = fun->shared()->CalculateInObjectProperties();
  Object* map_obj;
  { MaybeObject* maybe_map_obj =
        Heap::AllocateMap(JS_OBJECT_TYPE, instance_size);
    if (!maybe_map_obj->ToObject(&map_obj)) return maybe_map_obj;
  }


  Object* prototype;
  if (fun->has_instance_prototype()) {
    prototype = fun->instance_prototype();
  } else {
    { MaybeObject* maybe_prototype = AllocateFunctionPrototype(fun);
      if (!maybe_prototype->ToObject(&prototype)) return maybe_prototype;
    }
  }
  Map* map = Map::cast(map_obj);
  map->set_inobject_properties(in_object_properties);
  map->set_unused_property_fields(in_object_properties);
  map->set_prototype(prototype);
  ASSERT(map->has_fast_elements());


  ASSERT(in_object_properties <= Map::kMaxPreAllocatedPropertyFields);
  if (fun->shared()->CanGenerateInlineConstructor(prototype)) {
    int count = fun->shared()->this_property_assignments_count();
    if (count > in_object_properties) {

      fun->shared()->ForbidInlineConstructor();
    } else {
      Object* descriptors_obj;
      { MaybeObject* maybe_descriptors_obj = DescriptorArray::Allocate(count);
        if (!maybe_descriptors_obj->ToObject(&descriptors_obj)) {
          return maybe_descriptors_obj;
        }
      }
      DescriptorArray* descriptors = DescriptorArray::cast(descriptors_obj);
      for (int i = 0; i < count; i++) {
        String* name = fun->shared()->GetThisPropertyAssignmentName(i);
        ASSERT(name->IsSymbol());
        FieldDescriptor field(name, i, NONE);
        field.SetEnumerationIndex(i);
        descriptors->Set(i, &field);
      }
      descriptors->SetNextEnumerationIndex(count);
      descriptors->SortUnchecked();


      if (HasDuplicates(descriptors)) {
        fun->shared()->ForbidInlineConstructor();
      } else {
        map->set_instance_descriptors(descriptors);
        map->set_pre_allocated_property_fields(count);
        map->set_unused_property_fields(in_object_properties - count);
      }
    }
  }

  fun->shared()->StartInobjectSlackTracking(map);

  return map;
}
