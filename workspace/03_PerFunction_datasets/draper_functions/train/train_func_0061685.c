_backup_fieldanalysis_orc_same_parity_sad_planar_yuv (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int n = ex->n;
  const orc_int8 * ORC_RESTRICT ptr4;
  const orc_int8 * ORC_RESTRICT ptr5;
  orc_union32 var12 =  { 0 };
  orc_int8 var36;
  orc_int8 var37;
  orc_union32 var38;
  orc_union16 var39;
  orc_union16 var40;
  orc_union16 var41;
  orc_union16 var42;
  orc_union32 var43;
  orc_union32 var44;
  orc_union32 var45;

  ptr4 = (orc_int8 *)ex->arrays[4];
  ptr5 = (orc_int8 *)ex->arrays[5];


    var38.i = ex->params[24];

  for (i = 0; i < n; i++) {

    var36 = ptr4[i];

    var39.i = (orc_uint8)var36;

    var37 = ptr5[i];

    var40.i = (orc_uint8)var37;

    var41.i = var39.i - var40.i;

    var42.i = ORC_ABS(var41.i);

    var43.i = (orc_uint16)var42.i;

    var44.i = (var43.i > var38.i) ? (~0) : 0;

    var45.i = var43.i & var44.i;

    var12.i = var12.i + var45.i;
  }
  ex->accumulators[0] = var12.i;

}
