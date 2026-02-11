callAsFunction(ExecState *exec, JSObject * , const List &args)
{
  if (args.size() == 1) {

    return get( exec, Identifier(args[0]->toString(exec)) );
  }
  return jsUndefined();
}
