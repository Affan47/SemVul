value(VM &vm, const VarStyleObj *, Vector<size_t> &) const
{
  if (!color_)
    return vm.interp->makeFalse();
  else
    return color_;
}
