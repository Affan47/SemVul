GenerateLoadFunctionFromCell(JSGlobalPropertyCell* cell,
                                                    JSFunction* function,
                                                    Label* miss) {

  __ Move(rdi, Handle<JSGlobalPropertyCell>(cell));
  __ movq(rdi, FieldOperand(rdi, JSGlobalPropertyCell::kValueOffset));


  if (Heap::InNewSpace(function)) {


    __ JumpIfSmi(rdi, miss);
    __ CmpObjectType(rdi, JS_FUNCTION_TYPE, rax);
    __ j(not_equal, miss);


    __ Move(rax, Handle<SharedFunctionInfo>(function->shared()));
    __ cmpq(FieldOperand(rdi, JSFunction::kSharedFunctionInfoOffset), rax);
    __ j(not_equal, miss);
  } else {
    __ Cmp(rdi, Handle<JSFunction>(function));
    __ j(not_equal, miss);
  }
}
