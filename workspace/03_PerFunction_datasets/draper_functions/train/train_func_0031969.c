video_convert_orc_planar_chroma_422_420 (guint8 * ORC_RESTRICT d1, int d1_stride, const guint8 * ORC_RESTRICT s1, int s1_stride, const guint8 * ORC_RESTRICT s2, int s2_stride, int n, int m)
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
      1, 7, 9, 39, 118, 105, 100, 101, 111, 95, 99, 111, 110, 118, 101, 114,
      116, 95, 111, 114, 99, 95, 112, 108, 97, 110, 97, 114, 95, 99, 104, 114,
      111, 109, 97, 95, 52, 50, 50, 95, 52, 50, 48, 11, 1, 1, 12, 1,
      1, 12, 1, 1, 39, 0, 4, 5, 2, 0,
    };
    p = orc_program_new_from_static_bytecode (bc);
    orc_program_set_backup_function (p, _backup_video_convert_orc_planar_chroma_422_420);
#else
      p = orc_program_new ();
      orc_program_set_2d (p);
      orc_program_set_name (p, "video_convert_orc_planar_chroma_422_420");
      orc_program_set_backup_function (p, _backup_video_convert_orc_planar_chroma_422_420);
      orc_program_add_destination (p, 1, "d1");
      orc_program_add_source (p, 1, "s1");
      orc_program_add_source (p, 1, "s2");

      orc_program_append_2 (p, "avgub", 0, ORC_VAR_D1, ORC_VAR_S1, ORC_VAR_S2, ORC_VAR_D1);
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
  ORC_EXECUTOR_M(ex) = m;
  ex->arrays[ORC_VAR_D1] = d1;
  ex->params[ORC_VAR_D1] = d1_stride;
  ex->arrays[ORC_VAR_S1] = (void *)s1;
  ex->params[ORC_VAR_S1] = s1_stride;
  ex->arrays[ORC_VAR_S2] = (void *)s2;
  ex->params[ORC_VAR_S2] = s2_stride;

  func = c->exec;
  func (ex);
}
