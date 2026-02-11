collect_others_args(Node *overload) {
  String *overloaded_from = Getattr(overload, "sym:overloaded");
  String *others_args = NewString("");
  int first_overload = 1;

  for (Node *overload2 = overloaded_from; overload2; overload2 = Getattr(overload2, "sym:nextSibling")) {
    if (overload2 == overload || GetInt(overload2, "overload:ignore"))
      continue;

    ParmList *opl = parmlist_with_names(Getattr(overload2, "wrap:parms"));
    String *args = parmlist_str_id_converter(opl);
    if (!first_overload)
      Printf(others_args, "\n                           ");
    Printf(others_args, "(%s)", args);
    Delete(args);
    Delete(opl);
    first_overload = 0;
  }
  return others_args;
}
