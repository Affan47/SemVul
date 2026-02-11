EmitLoadGlobalSlotCheckExtensions(
    Slot* slot,
    TypeofState typeof_state,
    Label* slow) {
  Register context = rsi;
  Register temp = rdx;

  Scope* s = scope();
  while (s != NULL) {
    if (s->num_heap_slots() > 0) {
      if (s->calls_eval()) {

        __ cmpq(ContextOperand(context, Context::EXTENSION_INDEX),
                Immediate(0));
        __ j(not_equal, slow);
      }

      __ movq(temp, ContextOperand(context, Context::CLOSURE_INDEX));
      __ movq(temp, FieldOperand(temp, JSFunction::kContextOffset));

      context = temp;
    }


    if (!s->outer_scope_calls_eval() || s->is_eval_scope()) break;
    s = s->outer_scope();
  }

  if (s != NULL && s->is_eval_scope()) {


    NearLabel next, fast;
    if (!context.is(temp)) {
      __ movq(temp, context);
    }

    __ LoadRoot(kScratchRegister, Heap::kGlobalContextMapRootIndex);
    __ bind(&next);

    __ cmpq(kScratchRegister, FieldOperand(temp, HeapObject::kMapOffset));
    __ j(equal, &fast);

    __ cmpq(ContextOperand(temp, Context::EXTENSION_INDEX), Immediate(0));
    __ j(not_equal, slow);

    __ movq(temp, ContextOperand(temp, Context::CLOSURE_INDEX));
    __ movq(temp, FieldOperand(temp, JSFunction::kContextOffset));
    __ jmp(&next);
    __ bind(&fast);
  }


  __ movq(rax, GlobalObjectOperand());
  __ Move(rcx, slot->var()->name());
  Handle<Code> ic(Builtins::builtin(Builtins::LoadIC_Initialize));
  RelocInfo::Mode mode = (typeof_state == INSIDE_TYPEOF)
      ? RelocInfo::CODE_TARGET
      : RelocInfo::CODE_TARGET_CONTEXT;
  EmitCallIC(ic, mode);
}
