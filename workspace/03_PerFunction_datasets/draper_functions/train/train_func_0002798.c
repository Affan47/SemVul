HasCustomCallGenerator(JSFunction* function) {
  SharedFunctionInfo* info = function->shared();
  if (info->HasBuiltinFunctionId()) {
    BuiltinFunctionId id = info->builtin_function_id();
#define CALL_GENERATOR_CASE(name) if (id == k##name) return true;
    CUSTOM_CALL_IC_GENERATORS(CALL_GENERATOR_CASE)
#undef CALL_GENERATOR_CASE
  }
  CallOptimization optimization(function);
  if (optimization.is_simple_api_call()) {
    return true;
  }
  return false;
}
