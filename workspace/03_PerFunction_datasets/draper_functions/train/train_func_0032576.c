actual(const ConstPtr<InheritedC> &ic, const Location &loc,
			  Interpreter &interp, Vector<size_t> &dependencies)
{
  size_t ind = ic->index();
  for (size_t i = 0; i < dependencies.size(); i++) {
    if (dependencies[i] == ind) {
      interp.setNextLocation(loc);
      interp.message(InterpreterMessages::actualLoop,
		     StringMessageArg(ic->identifier()->name()));
      return interp.makeError();
    }
  }
  dependencies.push_back(ind);
  ConstPtr<InheritedC> spec;
  const VarStyleObj *style = 0;
  if (ind >= inheritedCInfo_.size())
    spec = ic;
  else {
    const InheritedCInfo *p = inheritedCInfo_[ind].pointer();
    if (!p)
      spec = ic;
    else if (p->cachedValue) {
      const Vector<size_t> &dep = p->dependencies;
      for (size_t i = 0; i < dep.size(); i++)
	dependencies.push_back(dep[i]);
      return p->cachedValue;
    }
    else {
      style = p->style;
      spec = p->spec;
    }
  }
  VM vm(interp);
  vm.styleStack = this;
  vm.specLevel = level_;
  return spec->value(vm, style, dependencies);
}
