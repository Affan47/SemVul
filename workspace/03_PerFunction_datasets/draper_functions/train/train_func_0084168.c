semantics (ErrorStream &err, PointCutContext &context) {
  ArgSet new_arg_bindings;

  check_arg_types (err, "pointcut", type ());

  if (!node ()) {

    for (unsigned a = 0; a < context.func ()->Arguments (); a++)
      new_arg_bindings.append (context.func ()->Argument (a));
  }
  else {
    CT_ExprList *args = ((CT_CallExpr*)node ())->Arguments ();
    for (int s = 0; s < args->Entries (); s++) {
      CTree *arg = args->Entry (s);


      if (arg->NodeName () != CT_SimpleName::NodeId ()) {
  err << sev_error << node ()->token ()->location ()
      << "pointcut argument " << s << " must be an identifier"
      << endMessage;
  new_arg_bindings.append (0);
  continue;
      }


      const char *name = ((CT_SimpleName*)arg)->Object ()->Name ();

      const CArgumentInfo *arginfo = get_binding (name, err, context);;

      new_arg_bindings.append (arginfo);
    }
  }


  CFunctionInfo *saved_func = context.func (_func);


  context.arg_bindings ().push (&new_arg_bindings);


  sem_args (err, context);


  context.arg_bindings ().pop ();

  context.func (saved_func);

  _possible_types = (JoinPointLoc::join_point_type)arg(0)->possible_types ();
}
