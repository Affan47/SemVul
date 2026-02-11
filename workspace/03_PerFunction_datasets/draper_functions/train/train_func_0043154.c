parse_fixup_v380_action (sc_int type, sc_int var_count,
                         sc_int var1, sc_int var2, sc_int var3)
{
  sc_vartype_t vt_key, vt_value;
  sc_int action_count;


  vt_key.string = "Actions";
  parse_push_key (vt_key, PROP_KEY_STRING);
  action_count = parse_get_child_count ();
  parse_pop_key ();


  vt_key.integer = action_count;
  parse_push_key (vt_key, PROP_KEY_INTEGER);
  vt_key.string = "Actions";
  parse_push_key (vt_key, PROP_KEY_STRING);


  vt_key.string = "Type";
  parse_push_key (vt_key, PROP_KEY_STRING);
  vt_value.integer = type;
  parse_put_property (vt_value, PROP_INTEGER);
  parse_pop_key ();

  vt_key.string = "Var1";
  parse_push_key (vt_key, PROP_KEY_STRING);
  vt_value.integer = var1;
  parse_put_property (vt_value, PROP_INTEGER);
  parse_pop_key ();

  if (var_count > 1)
    {
      vt_key.string = "Var2";
      parse_push_key (vt_key, PROP_KEY_STRING);
      vt_value.integer = var2;
      parse_put_property (vt_value, PROP_INTEGER);
      parse_pop_key ();
    }

  if (var_count > 2)
    {
      vt_key.string = "Var3";
      parse_push_key (vt_key, PROP_KEY_STRING);
      vt_value.integer = var3;
      parse_put_property (vt_value, PROP_INTEGER);
      parse_pop_key ();
    }

  parse_pop_key ();
  parse_pop_key ();
}
