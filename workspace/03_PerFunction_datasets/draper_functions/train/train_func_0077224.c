_backup_audio_convert_orc_pack_u32 (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int n = ex->n;
  orc_union32 * ORC_RESTRICT ptr0;
  const orc_union32 * ORC_RESTRICT ptr4;
  orc_union32 var33;
#if defined(__APPLE__) && __GNUC__ == 4 && __GNUC_MINOR__ == 2 && defined (__i386__)
  volatile orc_union32 var34;
#else
  orc_union32 var34;
#endif
  orc_union32 var35;
  orc_union32 var36;

  ptr0 = (orc_union32 *)ex->arrays[0];
  ptr4 = (orc_union32 *)ex->arrays[4];


    var34.i = (int)0x80000000;

  for (i = 0; i < n; i++) {

    var33 = ptr4[i];

    var36.i = var33.i ^ var34.i;

    var35.i = ((orc_uint32)var36.i) >> ex->params[24];

    ptr0[i] = var35;
  }

}
