check_derived_func (JPL_Class &cls, JPL_Function &func,
  PointCutContext &context, Binding &binding, Condition &cond) {
  Condition unused;
  bool do_subclasses = true;
  const set<int> &derived_classes = cls.derived_class_ids ();
  for (set<int>::const_iterator i = derived_classes.begin ();
    i != derived_classes.end (); ++i) {
    JPL_Class *derived = (JPL_Class*)cls.map (*i);

    const JPL_Name::CList &children = derived->children ();
    for (JPL_Name::CList::const_iterator i = children.begin ();
         i != children.end (); ++i) {
      if ((*i)->type () != JoinPointLoc::Function)
        continue;
      JPL_Function &curr = *(JPL_Function*)*i;
      if (!func.has_same_name_and_args (curr))
         continue;
      if (arg (0)->match (curr, context, binding, cond))
        return true;
    }

    if (do_subclasses && check_derived_func (*derived, func, context,
      binding, cond))
      return true;
  }
  return !do_subclasses;
}
