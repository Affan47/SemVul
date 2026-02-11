CouldBePositiveZero(AstNode* node) {
  Literal* literal = node->AsLiteral();
  if (literal != NULL) {
    Handle<Object> handle = literal->handle();
    if (handle->IsSmi()) {
      if (Smi::cast(*handle) != Smi::FromInt(0)) {
        return false;
      }
    } else if (handle->IsHeapNumber()) {

      return false;
    }
  }
  return true;
}
