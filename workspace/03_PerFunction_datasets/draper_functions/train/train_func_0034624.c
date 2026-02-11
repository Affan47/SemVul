cogorc_convert_AYUV_Y444 (guint8 * ORC_RESTRICT d1, int d1_stride, guint8 * ORC_RESTRICT d2, int d2_stride, guint8 * ORC_RESTRICT d3, int d3_stride, const guint8 * ORC_RESTRICT s1, int s1_stride, int n, int m)
{
  OrcExecutor _ex, *ex = &_ex;
  static volatile int p_inited = 0;
  static OrcProgram *p = 0;
  void (*func) (OrcExecutor *);

  if (!p_inited) {
    orc_once_mutex_lock ();
    if (!p_inited) {

      p = orc_program_new ();
      orc_program_set_2d (p);
      orc_program_set_name (p, "cogorc_convert_AYUV_Y444");
      orc_program_set_backup_function (p, _backup_cogorc_convert_AYUV_Y444);
      orc_program_add_destination (p, 1, "d1");
      orc_program_add_destination (p, 1, "d2");
      orc_program_add_destination (p, 1, "d3");
      orc_program_add_source (p, 4, "s1");
      orc_program_add_temporary (p, 2, "t1");
      orc_program_add_temporary (p, 2, "t2");

      orc_program_append_2 (p, "splitlw", 0, ORC_VAR_T2, ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_D1);
      orc_program_append_2 (p, "splitwb", 0, ORC_VAR_D3, ORC_VAR_D2, ORC_VAR_T2, ORC_VAR_D1);
      orc_program_append_2 (p, "select1wb", 0, ORC_VAR_D1, ORC_VAR_T1, ORC_VAR_D1, ORC_VAR_D1);

      orc_program_compile (p);
    }
    p_inited = TRUE;
    orc_once_mutex_unlock ();
  }
  ex->program = p;

  ex->n = n;
  ORC_EXECUTOR_M(ex) = m;
  ex->arrays[ORC_VAR_D1] = d1;
  ex->params[ORC_VAR_D1] = d1_stride;
  ex->arrays[ORC_VAR_D2] = d2;
  ex->params[ORC_VAR_D2] = d2_stride;
  ex->arrays[ORC_VAR_D3] = d3;
  ex->params[ORC_VAR_D3] = d3_stride;
  ex->arrays[ORC_VAR_S1] = (void *)s1;
  ex->params[ORC_VAR_S1] = s1_stride;

  func = p->code_exec;
  func (ex);
}
