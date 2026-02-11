audio_convert_orc_pack_u32 (guint8 * ORC_RESTRICT d1, const gint32 * ORC_RESTRICT s1, int p1, int n)
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
      1, 9, 26, 97, 117, 100, 105, 111, 95, 99, 111, 110, 118, 101, 114, 116,
      95, 111, 114, 99, 95, 112, 97, 99, 107, 95, 117, 51, 50, 11, 4, 4,
      12, 4, 4, 14, 4, 0, 0, 0, 128, 16, 4, 20, 4, 132, 32, 4,
      16, 126, 0, 32, 24, 2, 0,
    };
    p = orc_program_new_from_static_bytecode (bc);
    orc_program_set_backup_function (p, _backup_audio_convert_orc_pack_u32);
#else
      p = orc_program_new ();
      orc_program_set_name (p, "audio_convert_orc_pack_u32");
      orc_program_set_backup_function (p, _backup_audio_convert_orc_pack_u32);
      orc_program_add_destination (p, 4, "d1");
      orc_program_add_source (p, 4, "s1");
      orc_program_add_constant (p, 4, 0x80000000, "c1");
      orc_program_add_parameter (p, 4, "p1");
      orc_program_add_temporary (p, 4, "t1");

      orc_program_append_2 (p, "xorl", 0, ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_C1, ORC_VAR_D1);
      orc_program_append_2 (p, "shrul", 0, ORC_VAR_D1, ORC_VAR_T1, ORC_VAR_P1, ORC_VAR_D1);
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
  ex->params[ORC_VAR_P1] = p1;

  func = c->exec;
  func (ex);
}
