execute(VM &vm) const
{
  if (!vm.processingMode) {
    vm.interp->setNextLocation(loc_);
    vm.interp->message(InterpreterMessages::noCurrentProcessingMode);
    vm.sp = 0;
    return 0;
  }
  vm.needStack(1);
  *vm.sp++ = flowObj_->copy(*vm.interp);
  ((CompoundFlowObj *)vm.sp[-1])
    ->setContent(new (*vm.interp) ProcessChildrenSosofoObj(vm.processingMode));
  return next_.pointer();
}
