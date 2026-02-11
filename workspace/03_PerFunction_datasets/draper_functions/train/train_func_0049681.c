SetBreakPoint(Handle<BreakPointInfo> break_point_info,
                                   Handle<Object> break_point_object) {

  if (break_point_info->break_point_objects()->IsUndefined()) {
    break_point_info->set_break_point_objects(*break_point_object);
    return;
  }

  if (break_point_info->break_point_objects() == *break_point_object) return;

  if (!break_point_info->break_point_objects()->IsFixedArray()) {
    Handle<FixedArray> array = FACTORY->NewFixedArray(2);
    array->set(0, break_point_info->break_point_objects());
    array->set(1, *break_point_object);
    break_point_info->set_break_point_objects(*array);
    return;
  }

  Handle<FixedArray> old_array =
      Handle<FixedArray>(
          FixedArray::cast(break_point_info->break_point_objects()));
  Handle<FixedArray> new_array =
      FACTORY->NewFixedArray(old_array->length() + 1);
  for (int i = 0; i < old_array->length(); i++) {

    if (old_array->get(i) == *break_point_object) return;
    new_array->set(i, old_array->get(i));
  }

  new_array->set(old_array->length(), *break_point_object);
  break_point_info->set_break_point_objects(*new_array);
}
