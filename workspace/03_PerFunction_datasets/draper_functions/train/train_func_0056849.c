_backup_audio_orc_unpack_u24_32_swap (OrcExecutor * ORC_RESTRICT ex)
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
  orc_union32 var37;

  ptr0 = (orc_union32 *)ex->arrays[0];
  ptr4 = (orc_union32 *)ex->arrays[4];


    var34.i = (int)0x80000000;

  for (i = 0; i < n; i++) {

    var33 = ptr4[i];

    var36.i = ORC_SWAP_L(var33.i);

    var37.i = var36.i << 8;

    var35.i = var37.i ^ var34.i;

    ptr0[i] = var35;
  }

}
