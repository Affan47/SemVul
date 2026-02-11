_backup_orc_audio_convert_unpack_u8_double (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int n = ex->n;
  orc_union64 * ORC_RESTRICT ptr0;
  const orc_int8 * ORC_RESTRICT ptr4;
  orc_int8 var34;
#if defined(__APPLE__) && __GNUC__ == 4 && __GNUC_MINOR__ == 2 && defined (__i386__)
  volatile orc_union32 var35;
#else
  orc_union32 var35;
#endif
  orc_union64 var36;
  orc_union16 var37;
  orc_union32 var38;
  orc_union32 var39;
  orc_union32 var40;

  ptr0 = (orc_union64 *)ex->arrays[0];
  ptr4 = (orc_int8 *)ex->arrays[4];


    var35.i = (int)0x80000000;

  for (i = 0; i < n; i++) {

    var34 = ptr4[i];

    var37.i = (orc_uint8)var34;

    var38.i = (orc_uint16)var37.i;

    var39.i = var38.i << ex->params[24];

    var40.i = var39.i ^ var35.i;

    var36.f = var40.i;

    ptr0[i] = var36;
  }

}
