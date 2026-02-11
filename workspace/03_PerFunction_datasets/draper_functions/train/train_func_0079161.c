ProcessExternalMarking() {
  bool work_to_do = true;
  ASSERT(marking_stack_.is_empty());
  while (work_to_do) {
    MarkObjectGroups();
    MarkImplicitRefGroups();
    work_to_do = !marking_stack_.is_empty();
    ProcessMarkingStack();
  }
}
