CalculateLineEnds(Handle<String> src,
                                     bool with_last_line) {
  src = FlattenGetString(src);


  int line_count_estimate = src->length() >> 4;
  List<int> line_ends(line_count_estimate);
  Isolate* isolate = src->GetIsolate();
  {
    AssertNoAllocation no_heap_allocation;

    String::FlatContent content = src->GetFlatContent();
    ASSERT(content.IsFlat());
    if (content.IsAscii()) {
      CalculateLineEnds(isolate,
                        &line_ends,
                        content.ToAsciiVector(),
                        with_last_line);
    } else {
      CalculateLineEnds(isolate,
                        &line_ends,
                        content.ToUC16Vector(),
                        with_last_line);
    }
  }
  int line_count = line_ends.length();
  Handle<FixedArray> array = isolate->factory()->NewFixedArray(line_count);
  for (int i = 0; i < line_count; i++) {
    array->set(i, Smi::FromInt(line_ends[i]));
  }
  return array;
}
