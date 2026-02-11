GenerateArguments(CallRuntime* call) {


  ASSERT(function_state()->outer() == NULL);
  ASSERT(call->arguments()->length() == 1);
  CHECK_ALIVE(VisitForValue(call->arguments()->at(0)));
  HValue* index = Pop();
  HInstruction* elements = AddInstruction(new(zone()) HArgumentsElements);
  HInstruction* length = AddInstruction(new(zone()) HArgumentsLength(elements));
  HAccessArgumentsAt* result =
      new(zone()) HAccessArgumentsAt(elements, length, index);
  return ast_context()->ReturnInstruction(result, call->id());
}
