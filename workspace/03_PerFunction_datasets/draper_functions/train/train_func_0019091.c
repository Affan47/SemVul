cogorc_downsample_420_jpeg (guint8 * ORC_RESTRICT d1, const guint8 * ORC_RESTRICT s1, const guint8 * ORC_RESTRICT s2, int n)
{
  OrcExecutor _ex, *ex = &_ex;
  static volatile int p_inited = 0;
  static OrcProgram *p = 0;
  void (*func) (OrcExecutor *);

  if (!p_inited) {
    orc_once_mutex_lock ();
    if (!p_inited) {

      p = orc_program_new ();
      orc_program_set_name (p, "cogorc_downsample_420_jpeg");
      orc_program_set_backup_function (p, _backup_cogorc_downsample_420_jpeg);
      orc_program_add_destination (p, 1, "d1");
      orc_program_add_source (p, 2, "s1");
      orc_program_add_source (p, 2, "s2");
      orc_program_add_temporary (p, 2, "t1");
      orc_program_add_temporary (p, 1, "t2");
      orc_program_add_temporary (p, 1, "t3");
      orc_program_add_temporary (p, 1, "t4");
      orc_program_add_temporary (p, 1, "t5");

      orc_program_append_2 (p, "copyw", 0, ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "select0wb", 0, ORC_VAR_T2, ORC_VAR_T1, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "select1wb", 0, ORC_VAR_T3, ORC_VAR_T1, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "avgub", 0, ORC_VAR_T2, ORC_VAR_T2, ORC_VAR_T3, ORC_VAR_D1);
      orc_program_append_2 (p, "copyw", 0, ORC_VAR_T1, ORC_VAR_S2, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "select0wb", 0, ORC_VAR_T4, ORC_VAR_T1, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "select1wb", 0, ORC_VAR_T5, ORC_VAR_T1, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "avgub", 0, ORC_VAR_T4, ORC_VAR_T4, ORC_VAR_T5, ORC_VAR_D1);
      orc_program_append_2 (p, "avgub", 0, ORC_VAR_D1, ORC_VAR_T2, ORC_VAR_T4, ORC_VAR_D1);

      orc_program_compile (p);
    }
    p_inited = TRUE;
    orc_once_mutex_unlock ();
  }
  ex->program = p;

  ex->n = n;
  ex->arrays[ORC_VAR_D1] = d1;
  ex->arrays[ORC_VAR_S1] = (void *)s1;
  ex->arrays[ORC_VAR_S2] = (void *)s2;

  func = p->code_exec;
  func (ex);
}
