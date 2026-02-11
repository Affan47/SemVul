_backup_audio_orc_unpack_s16 (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int n = ex->n;
  orc_union32 * ORC_RESTRICT ptr0;
  const orc_union16 * ORC_RESTRICT ptr4;
  orc_union16 var33;
  orc_union32 var34;
  orc_union32 var35;

  ptr0 = (orc_union32 *)ex->arrays[0];
  ptr4 = (orc_union16 *)ex->arrays[4];


  for (i = 0; i < n; i++) {

    var33 = ptr4[i];

    var35.i = (orc_uint16)var33.i;

    var34.i = var35.i << 16;

    ptr0[i] = var34;
  }

}
