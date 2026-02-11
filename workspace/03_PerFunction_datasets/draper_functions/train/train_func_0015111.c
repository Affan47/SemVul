restr_pass_task_object_location (sc_gameref_t game,
                                 sc_int var1, sc_int var2, sc_int var3)
{
  const sc_var_setref_t vars = gs_get_vars (game);
  sc_bool should_be;
  sc_int object;

  if (restr_trace)
    {
      sc_trace ("Restr: running object"
                " location restriction, %ld, %ld, %ld\n", var1, var2, var3);
    }


  should_be = FALSE;
  object = -1;


  if (var2 >= 0 && var2 < 6)
    should_be = TRUE;
  else if (var2 >= 6 && var2 < 12)
    should_be = FALSE;
  else
    sc_fatal ("restr_pass_task_object_location: bad var2, %ld\n", var2);


  if (var1 == 0)
    {
      object = -1;
      should_be = !should_be;
    }
  else if (var1 == 1)
    object = -1;
  else if (var1 == 2)
    object = var_get_ref_object (vars);
  else if (var1 >= 3)
    object = obj_dynamic_object (game, var1 - 3);
  else
    sc_fatal ("restr_pass_task_object_location: bad var1, %ld\n", var1);


  if (var1 == 2 && object != -1 && obj_is_static (game, object))
    {
      if (restr_trace)
        {
          sc_trace ("Restr:"
                    " restriction object %ld is static, rejecting\n", object);
        }

      return FALSE;
    }


  if (object == -1)
    {
      sc_int target;

      for (target = 0; target < gs_object_count (game); target++)
        {
          if (restr_object_in_place (game, target, var2, var3))
            return should_be;
        }
      return !should_be;
    }
  return should_be == restr_object_in_place (game, object, var2, var3);
}
