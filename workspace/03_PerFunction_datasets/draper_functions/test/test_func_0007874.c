CouldBeNaN(const Result& result) {
  if (result.type_info().IsSmi()) return false;
  if (result.type_info().IsInteger32()) return false;
  if (!result.is_constant()) return true;
  if (!result.handle()->IsHeapNumber()) return false;
  return isnan(HeapNumber::cast(*result.handle())->value());
}
