SpillElementAt(int index) {
  if (!elements_[index].is_valid()) return;

  SyncElementAt(index);


  TypeInfo info;
  if (!elements_[index].is_copy()) {
    info = elements_[index].type_info();
  } else {
    info = elements_[elements_[index].index()].type_info();
  }

  FrameElement new_element = FrameElement::MemoryElement(info);
  if (elements_[index].is_copied()) {
    new_element.set_copied();
  }
  if (elements_[index].is_untagged_int32()) {
    new_element.set_untagged_int32(true);
  }
  if (elements_[index].is_register()) {
    Unuse(elements_[index].reg());
  }
  elements_[index] = new_element;
}
