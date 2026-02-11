adder_orc_add_volume_f64 (double * ORC_RESTRICT d1, const double * ORC_RESTRICT s1, double p1, int n)
{
  OrcExecutor _ex, *ex = &_ex;
  static volatile int p_inited = 0;
  static OrcCode *c = 0;
  void (*func) (OrcExecutor *);

  if (!p_inited) {
    orc_once_mutex_lock ();
    if (!p_inited) {
      OrcProgram *p;

#if 1
    static const orc_uint8 bc[] = {
      1, 9, 24, 97, 100, 100, 101, 114, 95, 111, 114, 99, 95, 97, 100, 100,
      95, 118, 111, 108, 117, 109, 101, 95, 102, 54, 52, 11, 8, 8, 12, 8,
      8, 18, 8, 20, 8, 214, 32, 4, 24, 212, 0, 0, 32, 2, 0,     };
    p = orc_program_new_from_static_bytecode (bc);
    orc_program_set_backup_function (p, _backup_adder_orc_add_volume_f64);
#else
      p = orc_program_new ();
      orc_program_set_name (p, "adder_orc_add_volume_f64");
      orc_program_set_backup_function (p, _backup_adder_orc_add_volume_f64);
      orc_program_add_destination (p, 8, "d1");
      orc_program_add_source (p, 8, "s1");
      orc_program_add_parameter_double (p, 8, "p1");
      orc_program_add_temporary (p, 8, "t1");

      orc_program_append_2 (p, "muld", 0, ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_P1, ORC_VAR_D1);
      orc_program_append_2 (p, "addd", 0, ORC_VAR_D1, ORC_VAR_D1, ORC_VAR_T1, ORC_VAR_D1);
#endif

      orc_program_compile (p);
      c = orc_program_take_code (p);
      orc_program_free (p);
    }
    p_inited = TRUE;
    orc_once_mutex_unlock ();
  }
  ex->arrays[ORC_VAR_A2] = c;
  ex->program = 0;

  ex->n = n;
  ex->arrays[ORC_VAR_D1] = d1;
  ex->arrays[ORC_VAR_S1] = (void *)s1;
  {
    orc_union64 tmp;
    tmp.f = p1;
    ex->params[ORC_VAR_P1] = tmp.x2[0];
    ex->params[ORC_VAR_T1] = tmp.x2[1];
  }

  func = c->exec;
  func (ex);
}
