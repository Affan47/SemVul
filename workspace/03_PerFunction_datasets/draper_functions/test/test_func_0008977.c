cogorc_planar_chroma_444_420 (orc_uint8 * ORC_RESTRICT d1, int d1_stride, const orc_uint16 * ORC_RESTRICT s1, int s1_stride, const orc_uint16 * ORC_RESTRICT s2, int s2_stride, int n, int m)
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
      orc_program_set_name (p, "cogorc_planar_chroma_444_420");
      orc_program_set_backup_function (p, _backup_cogorc_planar_chroma_444_420);
      orc_program_add_destination (p, 1, "d1");
      orc_program_add_source (p, 2, "s1");
      orc_program_add_source (p, 2, "s2");
      orc_program_add_temporary (p, 2, "t1");
      orc_program_add_temporary (p, 1, "t2");
      orc_program_add_temporary (p, 1, "t3");

      orc_program_append_2 (p, "avgub", 1, ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_S2, ORC_VAR_D1);
      orc_program_append_2 (p, "splitwb", 0, ORC_VAR_T2, ORC_VAR_T3, ORC_VAR_T1, ORC_VAR_D1);
      orc_program_append_2 (p, "avgub", 0, ORC_VAR_D1, ORC_VAR_T2, ORC_VAR_T3, ORC_VAR_D1);

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
  ex->arrays[ORC_VAR_S1] = (void *)s1;
  ex->params[ORC_VAR_S1] = s1_stride;
  ex->arrays[ORC_VAR_S2] = (void *)s2;
  ex->params[ORC_VAR_S2] = s2_stride;

  func = p->code_exec;
  func (ex);
}
