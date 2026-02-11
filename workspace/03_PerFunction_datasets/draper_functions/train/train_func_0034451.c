evaluate (JoinPointLoc &jpl, PointCutContext &context,
                         Binding &binding, Condition &cond) {
  if (jpl.type () != JoinPointLoc::MethodCall)
    return false;

  JoinPointLoc::join_point_type pt = (JoinPointLoc::join_point_type)arg (0)->possible_types();


  JPL_Function *target_function = ((JPL_MethodCall&)jpl).target_function ();
  if (pt & JoinPointLoc::Function)
    if (arg (0)->match (*target_function, context, binding, cond))
      return true;


  if (pt & (JoinPointLoc::Aspect | JoinPointLoc::Class)) {
    JPL_Name *scope = target_function->parent ();
    return scope && check_scopes (scope, context, binding, cond);
  }

  return false;
}
