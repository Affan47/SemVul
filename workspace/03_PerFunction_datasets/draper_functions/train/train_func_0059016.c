LocalLookup(Handle<String> name) {
  Variable* result = variables_.Lookup(name);
  if (result != NULL || scope_info_.is_null()) {
    return result;
  }


  ASSERT(*name != *isolate_->factory()->arguments_symbol());

  ASSERT(scope_info_->StackSlotIndex(*name) < 0);


  Variable::Mode mode;
  int index = scope_info_->ContextSlotIndex(*name, &mode);
  if (index < 0) {

    mode = Variable::VAR;
    index = scope_info_->ParameterIndex(*name);
    if (index < 0) {

      index = scope_info_->FunctionContextSlotIndex(*name);
      if (index < 0) return NULL;
    }
  }

  Variable* var =
      variables_.Declare(this, name, mode, true, Variable::NORMAL);
  var->AllocateTo(Variable::CONTEXT, index);
  return var;
}
