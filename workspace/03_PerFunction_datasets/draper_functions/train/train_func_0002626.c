hb_utf16_script_run_next(unsigned *num_code_points, HB_ScriptItem *output,
                         const uint16_t *chars, size_t len, ssize_t *iter) {
  if (*iter == len)
    return 0;

  output->pos = *iter;
  {
  const uint32_t init_cp = utf16_to_code_point(chars, len, iter);
  unsigned cps = 1;
  if (init_cp == HB_InvalidCodePoint)
    return 0;
  {
  const HB_Script init_script = code_point_to_script(init_cp);
  HB_Script current_script = init_script;
  output->script = init_script;

  for (;;) {
    if (*iter == len)
      break;
    {
    const ssize_t prev_iter = *iter;
    const uint32_t cp = utf16_to_code_point(chars, len, iter);
    if (cp == HB_InvalidCodePoint)
      return 0;
    cps++;
    {
       const HB_Script script = code_point_to_script(cp);

    if (script != current_script) {
      if (current_script == HB_Script_Inherited && init_script == HB_Script_Inherited) {

        output->script = script;
        current_script = script;
        continue;
      } else if (script == HB_Script_Inherited) {
        current_script = script;
        continue;
      } else {
        *iter = prev_iter;
        cps--;
        break;
      }
    }
  }

  if (output->script == HB_Script_Inherited)
    output->script = HB_Script_Common;

  output->length = *iter - output->pos;
  if (num_code_points)
    *num_code_points = cps;
  }
  }
  }
  }
  return 1;
}
