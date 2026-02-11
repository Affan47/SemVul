_backup_orc_audio_convert_unpack_float_double_swap (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int n = ex->n;
  orc_union64 * ORC_RESTRICT ptr0;
  const orc_union32 * ORC_RESTRICT ptr4;
  orc_union32 var33;
  orc_union64 var34;
  orc_union32 var35;

  ptr0 = (orc_union64 *)ex->arrays[0];
  ptr4 = (orc_union32 *)ex->arrays[4];


  for (i = 0; i < n; i++) {

    var33 = ptr4[i];

    var35.i = ORC_SWAP_L(var33.i);

    {
       orc_union32 _src1;
       _src1.i = ORC_DENORMAL(var35.i);
       var34.f = _src1.f;
    }

    ptr0[i] = var34;
  }

}
