video_convert_orc_getline_Y800 (guint8 * ORC_RESTRICT d1, const guint8 * ORC_RESTRICT s1, int n)
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
      1, 9, 30, 118, 105, 100, 101, 111, 95, 99, 111, 110, 118, 101, 114, 116,
      95, 111, 114, 99, 95, 103, 101, 116, 108, 105, 110, 101, 95, 89, 56, 48,
      48, 11, 4, 4, 12, 1, 1, 14, 1, 255, 0, 0, 0, 14, 2, 128,
      128, 0, 0, 20, 2, 196, 32, 16, 4, 195, 0, 32, 17, 2, 0,     };
    p = orc_program_new_from_static_bytecode (bc);
    orc_program_set_backup_function (p, _backup_video_convert_orc_getline_Y800);
#else
      p = orc_program_new ();
      orc_program_set_name (p, "video_convert_orc_getline_Y800");
      orc_program_set_backup_function (p, _backup_video_convert_orc_getline_Y800);
      orc_program_add_destination (p, 4, "d1");
      orc_program_add_source (p, 1, "s1");
      orc_program_add_constant (p, 1, 0x000000ff, "c1");
      orc_program_add_constant (p, 2, 0x00008080, "c2");
      orc_program_add_temporary (p, 2, "t1");

      orc_program_append_2 (p, "mergebw", 0, ORC_VAR_T1, ORC_VAR_C1, ORC_VAR_S1, ORC_VAR_D1);
      orc_program_append_2 (p, "mergewl", 0, ORC_VAR_D1, ORC_VAR_T1, ORC_VAR_C2, ORC_VAR_D1);
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

  func = c->exec;
  func (ex);
}
