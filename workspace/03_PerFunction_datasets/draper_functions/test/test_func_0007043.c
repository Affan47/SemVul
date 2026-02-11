CompileCustomCall(Object* object,
                                                 JSObject* holder,
                                                 JSGlobalPropertyCell* cell,
                                                 JSFunction* function,
                                                 String* fname) {
  ASSERT(HasCustomCallGenerator(function));

  SharedFunctionInfo* info = function->shared();
  if (info->HasBuiltinFunctionId()) {
    BuiltinFunctionId id = info->builtin_function_id();
#define CALL_GENERATOR_CASE(name)                           \
    if (id == k##name) {                                    \
      return CallStubCompiler::Compile##name##Call(object,  \
                                                  holder,   \
                                                  cell,     \
                                                  function, \
                                                  fname);   \
    }
    CUSTOM_CALL_IC_GENERATORS(CALL_GENERATOR_CASE)
#undef CALL_GENERATOR_CASE
  }
  CallOptimization optimization(function);
  ASSERT(optimization.is_simple_api_call());
  return CompileFastApiCall(optimization,
                            object,
                            holder,
                            cell,
                            function,
                            fname);
}
