get_binding (const char *name,
						ErrorStream &err,
						PointCutContext &context) {
  if (!context.func ()) {
    err << sev_error << node ()->token ()->location ()
	<< "context variable '" << name
	<< "' is not support in this kind of pointcut expression"
	<< endMessage;
    return 0;
  }
  ArgSet &curr_arg_bindings = *context.arg_bindings ().top ();
  CArgumentInfo *arginfo = (CArgumentInfo*)0;
  unsigned int a;
  for (a = 0; a < context.func ()->Arguments (); a++) {
    if (strcmp (context.func ()->Argument (a)->Name (), name) == 0) {
      arginfo = context.func ()->Argument (a);
      break;
    }
  }
  if (!arginfo) {
    err << sev_error << node ()->token ()->location ()
	<< "'" << name
	<< "' is not in argument list" << endMessage;
    return 0;
  }
  return curr_arg_bindings.lookup (a);
}
