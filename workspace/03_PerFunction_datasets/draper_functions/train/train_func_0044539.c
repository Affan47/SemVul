CompileLazy(CompilationInfo* info) {
  Isolate* isolate = info->isolate();

  ZoneScope zone_scope(isolate, DELETE_ON_EXIT);


  VMState state(isolate, COMPILER);

  PostponeInterruptsScope postpone(isolate);

  Handle<SharedFunctionInfo> shared = info->shared_info();
  int compiled_size = shared->end_position() - shared->start_position();
  isolate->counters()->total_compile_size()->Increment(compiled_size);


  if (ParserApi::Parse(info)) {


    HistogramTimerScope timer(isolate->counters()->compile_lazy());


    if (info->function()->strict_mode()) {
      shared->set_strict_mode(true);
      info->MarkAsStrictMode();
    }


    if (!MakeCode(info)) {
      if (!isolate->has_pending_exception()) {
        isolate->StackOverflow();
      }
    } else {
      ASSERT(!info->code().is_null());
      Handle<Code> code = info->code();


      if (shared->optimization_disabled()) code->set_optimizable(false);

      Handle<JSFunction> function = info->closure();
      RecordFunctionCompilation(Logger::LAZY_COMPILE_TAG, info, shared);

      if (info->IsOptimizing()) {
        ASSERT(shared->scope_info() != SerializedScopeInfo::Empty());
        function->ReplaceCode(*code);
      } else {


        Handle<SerializedScopeInfo> scope_info =
            SerializedScopeInfo::Create(info->scope());
        shared->set_scope_info(*scope_info);
        shared->set_code(*code);
        if (!function.is_null()) {
          function->ReplaceCode(*code);
          ASSERT(!function->IsOptimized());
        }


        FunctionLiteral* lit = info->function();
        int expected = lit->expected_property_count();
        SetExpectedNofPropertiesFromEstimate(shared, expected);


        shared->SetThisPropertyAssignmentsInfo(
            lit->has_only_simple_this_property_assignments(),
            *lit->this_property_assignments());


        ASSERT(shared->is_compiled());
        shared->set_code_age(0);

        if (info->AllowOptimize() && !shared->optimization_disabled()) {


          if (FLAG_always_opt &&
              !Isolate::Current()->DebuggerHasBreakPoints()) {
            CompilationInfo optimized(function);
            optimized.SetOptimizing(AstNode::kNoNumber);
            return CompileLazy(&optimized);
          }
        }
      }

      return true;
    }
  }

  ASSERT(info->code().is_null());
  return false;
}
