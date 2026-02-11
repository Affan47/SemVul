EvacuateShortcutCandidate(Map* map,
                                               HeapObject** slot,
                                               HeapObject* object) {
    ASSERT(IsShortcutCandidate(map->instance_type()));

    if (ConsString::cast(object)->unchecked_second() == Heap::empty_string()) {
      HeapObject* first =
          HeapObject::cast(ConsString::cast(object)->unchecked_first());

      *slot = first;

      if (!Heap::InNewSpace(first)) {
        object->set_map_word(MapWord::FromForwardingAddress(first));
        return;
      }

      MapWord first_word = first->map_word();
      if (first_word.IsForwardingAddress()) {
        HeapObject* target = first_word.ToForwardingAddress();

        *slot = target;
        object->set_map_word(MapWord::FromForwardingAddress(target));
        return;
      }

      Scavenge(first->map(), slot, first);
      object->set_map_word(MapWord::FromForwardingAddress(*slot));
      return;
    }

    int object_size = ConsString::kSize;
    EvacuateObject<POINTER_OBJECT, SMALL>(map, slot, object, object_size);
  }
