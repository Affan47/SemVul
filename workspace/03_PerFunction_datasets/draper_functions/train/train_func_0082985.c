PushTryHandler(CodeLocation try_location,
                                    HandlerType type) {

  STATIC_ASSERT(StackHandlerConstants::kSize == 5 * kPointerSize);
  STATIC_ASSERT(StackHandlerConstants::kNextOffset == 0 * kPointerSize);
  STATIC_ASSERT(StackHandlerConstants::kContextOffset == 1 * kPointerSize);
  STATIC_ASSERT(StackHandlerConstants::kFPOffset == 2 * kPointerSize);
  STATIC_ASSERT(StackHandlerConstants::kStateOffset == 3 * kPointerSize);
  STATIC_ASSERT(StackHandlerConstants::kPCOffset == 4 * kPointerSize);


  if (try_location == IN_JAVASCRIPT) {
    if (type == TRY_CATCH_HANDLER) {
      push(Immediate(StackHandler::TRY_CATCH));
    } else {
      push(Immediate(StackHandler::TRY_FINALLY));
    }
    push(rbp);
    push(rsi);
  } else {
    ASSERT(try_location == IN_JS_ENTRY);


    push(Immediate(StackHandler::ENTRY));
    push(Immediate(0));
    Push(Smi::FromInt(0));
  }

  Operand handler_operand =
      ExternalOperand(ExternalReference(Isolate::kHandlerAddress, isolate()));
  push(handler_operand);

  movq(handler_operand, rsp);
}
