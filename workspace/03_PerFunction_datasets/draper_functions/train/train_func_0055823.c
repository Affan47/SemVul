create_statemachine_definition()
{
  statemachine_definition *def;
  def = statemachine_definition_new(HTMLPARSER_NUM_STATES);
  if (def == NULL)
    return NULL;

  statemachine_definition_populate(def, htmlparser_state_transitions,
                                   htmlparser_states_internal_names);

  statemachine_enter_state(def, HTMLPARSER_STATE_INT_TAG_NAME,
                           enter_tag_name);
  statemachine_exit_state(def, HTMLPARSER_STATE_INT_TAG_NAME, exit_tag_name);

  statemachine_enter_state(def, HTMLPARSER_STATE_INT_ATTR, enter_attr);
  statemachine_exit_state(def, HTMLPARSER_STATE_INT_ATTR, exit_attr);

  statemachine_enter_state(def, HTMLPARSER_STATE_INT_TAG_CLOSE, tag_close);


  statemachine_in_state(def, HTMLPARSER_STATE_INT_CDATA_TEXT, in_state_cdata);
  statemachine_in_state(def, HTMLPARSER_STATE_INT_CDATA_COMMENT_START,
                        in_state_cdata);
  statemachine_in_state(def, HTMLPARSER_STATE_INT_CDATA_COMMENT_START_DASH,
                        in_state_cdata);
  statemachine_in_state(def, HTMLPARSER_STATE_INT_CDATA_COMMENT_BODY,
                        in_state_cdata);
  statemachine_in_state(def, HTMLPARSER_STATE_INT_CDATA_COMMENT_DASH,
                        in_state_cdata);
  statemachine_in_state(def, HTMLPARSER_STATE_INT_CDATA_COMMENT_DASH_DASH,
                        in_state_cdata);
  statemachine_in_state(def, HTMLPARSER_STATE_INT_CDATA_LT, in_state_cdata);
  statemachine_in_state(def, HTMLPARSER_STATE_INT_CDATA_MAY_CLOSE,
                        in_state_cdata);


  statemachine_in_state(def, HTMLPARSER_STATE_INT_JS_FILE, in_state_cdata);

  statemachine_enter_state(def, HTMLPARSER_STATE_INT_CDATA_MAY_CLOSE,
                           enter_state_cdata_may_close);
  statemachine_exit_state(def, HTMLPARSER_STATE_INT_CDATA_MAY_CLOSE,
                          exit_state_cdata_may_close);

  statemachine_enter_state(def, HTMLPARSER_STATE_INT_VALUE, enter_value);


  statemachine_enter_state(def, HTMLPARSER_STATE_INT_VALUE_TEXT,
                           enter_value_content);
  statemachine_enter_state(def, HTMLPARSER_STATE_INT_VALUE_Q,
                           enter_value_content);
  statemachine_enter_state(def, HTMLPARSER_STATE_INT_VALUE_DQ,
                           enter_value_content);


  statemachine_exit_state(def, HTMLPARSER_STATE_INT_VALUE_TEXT,
                          exit_value_content);
  statemachine_exit_state(def, HTMLPARSER_STATE_INT_VALUE_Q,
                          exit_value_content);
  statemachine_exit_state(def, HTMLPARSER_STATE_INT_VALUE_DQ,
                          exit_value_content);

  statemachine_in_state(def, HTMLPARSER_STATE_INT_VALUE_TEXT, in_state_value);
  statemachine_in_state(def, HTMLPARSER_STATE_INT_VALUE_Q, in_state_value);
  statemachine_in_state(def, HTMLPARSER_STATE_INT_VALUE_DQ, in_state_value);

  return def;
}
