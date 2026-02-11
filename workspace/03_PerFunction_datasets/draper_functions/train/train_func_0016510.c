we_guied_get_pointer_to_bool_value(gpointer object, gint column)
{
  gboolean *value = NULL;

  switch (column) {
  case PLUGIN_ENABLED:
    value = &((Plugin *) object)->enabled;
    break;

  case TRIGGER_ENABLED:
    value = &((Trigger *) object)->enabled;
    break;

  case TRIGGER_GAG:
    value = &((Trigger *) object)->gag_output;
    break;

  case TRIGGER_GAGLOG:
    value = &((Trigger *) object)->gag_log;
    break;

  case TRIGGER_KEEPEXEC:
    value = &((Trigger *) object)->keepexecuting;
    break;

  case TRIGGER_REWRITER:
    value = &((Trigger *) object)->rewriter;
    break;

  case TRIGGER_ICASE:
    value = &((Trigger *) object)->ignore_case;
    break;

  case TRIGGER_HIGHLIGHT:
    value = &((Trigger *) object)->highlight;
    break;

  case ALIAS_ENABLED:
    value = &((Alias *) object)->enabled;
    break;

  case ALIAS_PERL_EVAL:
    value = &((Alias *) object)->perl_eval;
    break;

  case ALIAS_ICASE:
    value = &((Alias *) object)->ignore_case;
    break;

  case TIMER_ENABLED:
    value = &((Timer *) object)->enabled;
    break;

  case TIMER_TEMPORARY:
    value = &((Timer *) object)->temporary;
    break;

  case MACRO_ENABLED:
    value = &((Macro *) object)->enabled;
    break;

  case HOOK_ENABLED:
    value = &((Hook *) object)->enabled;
    break;
  }

  return value;
}
