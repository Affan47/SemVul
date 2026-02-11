execute(VM &vm) const
{
  if (!vm.sp[-1]->isTrue())
    return next_.pointer();
  --vm.sp;
  return nextTest_.pointer();
}
