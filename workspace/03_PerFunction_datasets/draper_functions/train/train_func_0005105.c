insert (Unit *unit, Token *token, bool after) {
  if (_config.noline ())
    return false;
  if (unit && token && unit->isMacroExp ()) {
    if (after)
      token = ((MacroUnit*)unit)->ExpansionEnd (token);
    else
      token = ((MacroUnit*)unit)->ExpansionBegin (token);
    unit  = (Unit*)token->belonging_to ();
  }
  if (unit && unit->isMacroExp ()) {
    return false;
  }
  CUnit line_directive (_err);
  directive (line_directive, unit, token);
  line_directive << endu;
  Unit *ins_unit = (Unit*)token->belonging_to ();
  if (after)
    ins_unit->move (token, line_directive);
  else
    ins_unit->move_before (token, line_directive);
  return true;
}
