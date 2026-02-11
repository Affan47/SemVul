_backup_audio_convert_orc_pack_double_float_swap (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int n = ex->n;
  orc_union32 * ORC_RESTRICT ptr0;
  const orc_union64 * ORC_RESTRICT ptr4;
  orc_union64 var33;
  orc_union32 var34;
  orc_union32 var35;

  ptr0 = (orc_union32 *)ex->arrays[0];
  ptr4 = (orc_union64 *)ex->arrays[4];


  for (i = 0; i < n; i++) {

    var33 = ptr4[i];

    {
       orc_union64 _src1;
       orc_union32 _dest;
       _src1.i = ORC_DENORMAL_DOUBLE(var33.i);
       _dest.f = _src1.f;
       var35.i = ORC_DENORMAL(_dest.i);
    }

    var34.i = ORC_SWAP_L(var35.i);

    ptr0[i] = var34;
  }

}
