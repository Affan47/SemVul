_backup_adder_orc_volume_s32 (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int n = ex->n;
  orc_union32 * ORC_RESTRICT ptr0;
  orc_union32 var33;
  orc_union32 var34;
  orc_union32 var35;
  orc_union64 var36;
  orc_union64 var37;

  ptr0 = (orc_union32 *)ex->arrays[0];


    var34.i = ex->params[24];

  for (i = 0; i < n; i++) {

    var33 = ptr0[i];

    var36.i = ((orc_int64)var33.i) * ((orc_int64)var34.i);

    var37.i = var36.i >> 27;

    var35.i = ORC_CLAMP_SL(var37.i);

    ptr0[i] = var35;
  }

}
