update(int scope)
{
  Scope* tmpScope = d_scope;
  DebugAssert(scope < 0 || d_scope->level() <= scope,
	      "ContextObj::update(scope="+int2string(scope)
	      +"): scope < d_scope->level() = "
	      +int2string(d_scope->level()));
  d_scope = d_scope->topScope();
  if (scope >= 0) {

    for(int i=level(); i>scope; --i) {
      d_scope = d_scope->prevScope();
      DebugAssert(d_scope != NULL, "ContextObj::update["
		  +name()+"]: d_scope == NULL");
    }
  }
  ContextObj* data = makeCopy(getCMM());
  data->d_scope = tmpScope;

  data->d_restore=NULL;
  IF_DEBUG(data->setName(name()+" [copy]");)
  d_restore = new(getCMM()) ContextObjChain(data, this, d_restore);
  d_scope->addToChain(d_restore);
}
