value(VM &vm, const VarStyleObj *style,
			    Vector<size_t> &dependencies) const
{
  EvalContext::CurrentNodeSetter cns(style->node(), 0, vm);
  vm.actualDependencies = &dependencies;
  return vm.eval(code_.pointer(), style->display());
}
