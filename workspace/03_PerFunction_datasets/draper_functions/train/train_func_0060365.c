shuffle(VM &vm, const Location &loc)
{
  int nArgs = vm.nActualArgs;
  ELObj *func = vm.sp[-nArgs];
  for (int i = nArgs - 2; i > 0; i--)
    vm.sp[-i - 2] = vm.sp[-i - 1];
  vm.nActualArgs = nArgs - 2;
  ELObj *list = *--vm.sp;
  --vm.sp;
  while (!list->isNil()) {
    PairObj *tem = list->asPair();
    if (!tem) {
      vm.interp->setNextLocation(loc);
      vm.interp->message(InterpreterMessages::notAList,
			 StringMessageArg(vm.interp->makeStringC("apply")),
			 OrdinalMessageArg(nArgs),
			 ELObjMessageArg(list, *vm.interp));
      vm.sp = 0;
      return 0;
    }
    vm.needStack(1);
    vm.nActualArgs++;
    *vm.sp++ = tem->car();
    list = tem->cdr();
  }
  vm.needStack(1);
  *vm.sp++ = func;
  return 1;
}
