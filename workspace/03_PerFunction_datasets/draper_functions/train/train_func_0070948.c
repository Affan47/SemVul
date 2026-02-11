gen_binding_templates (ostream &out, const char *jpname,
                                      const BackEndProblems &bep) {

  for (int a = 0; a < _before.length (); a++)
    _before[a]->gen_binding_template (out, jpname, bep);
  if (around())
    around ()->gen_binding_template (out, jpname, bep);
  if (_next)
    _next->gen_binding_templates (out, jpname, bep);
  for (int a = 0; a < _after.length (); a++)
    _after[a]->gen_binding_template (out, jpname, bep);
}
