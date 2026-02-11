enter_scope ()
{
  if (func_def_f)
    func_def_f = 0;
  else
    scope_level++;
}
