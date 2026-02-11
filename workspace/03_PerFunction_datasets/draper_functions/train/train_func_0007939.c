callAsFunction(ExecState* exec, JSObject* thisObj, const List& args)
{
  assert(thisObj);

#ifdef KJS_VERBOSE
  ++callDepth;
#endif

  Debugger* dbg = exec->dynamicInterpreter()->debugger();


  FunctionExecState newExec(exec->dynamicInterpreter(), thisObj, body.get(), exec, this);
  if (exec->hadException())
    newExec.setException(exec->exception());

  FunctionBodyNode* body = this->body.get();


  CompileType currentState = body->compileState();
  if (currentState == NotCompiled) {
    initialCompile(&newExec);
  } else {

    CompileType desiredState = dbg ? Debug : Release;
    if (desiredState != currentState)
        body->compile(FunctionCode, desiredState);
  }

  size_t stackSize              = 0;
  LocalStorageEntry* stackSpace = 0;


  int regs   = body->numLocalsAndRegisters();
  stackSize  = sizeof(LocalStorageEntry) * regs;
  stackSpace = (LocalStorageEntry*)exec->dynamicInterpreter()->stackAlloc(stackSize);

  ActivationImp* activation = static_cast<ActivationImp*>(newExec.activationObject());
  activation->setup(&newExec, this, &args, stackSpace);
  activation->tearOffNeededSlot() = body->tearOffAtEnd();

  newExec.initLocalStorage(stackSpace, regs);

  JSValue* result = Machine::runBlock(&newExec, body->code(), exec);


  if (activation->tearOffNeededSlot()) {
    activation->performTearOff();
  } else {


    activation->scopeLink().deref();
    activation->localStorage = 0;
    exec->dynamicInterpreter()->recycleActivation(activation);
  }


  exec->dynamicInterpreter()->stackFree(stackSize);

#ifdef KJS_VERBOSE
  fprintf(stderr, "%s", ind());
  if (exec->exception())
    printInfo(exec,"throwing", exec->exception());
  else
    printInfo(exec,"returning", result);

  --callDepth;
#endif

  return result;
}
