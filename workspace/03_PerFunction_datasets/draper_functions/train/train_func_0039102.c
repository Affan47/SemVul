_backup_cogorc_combine4_u8 (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int n = ex->n;
  orc_int8 * ORC_RESTRICT ptr0;
  const orc_int8 * ORC_RESTRICT ptr4;
  const orc_int8 * ORC_RESTRICT ptr5;
  const orc_int8 * ORC_RESTRICT ptr6;
  const orc_int8 * ORC_RESTRICT ptr7;
  orc_int8 var34;
  orc_union16 var35;
  orc_int8 var36;
  orc_union16 var37;
  orc_int8 var38;
  orc_union16 var39;
  orc_int8 var40;
  orc_union16 var41;
#if defined(__APPLE__) && __GNUC__ == 4 && __GNUC_MINOR__ == 2 && defined (__i386__)
  volatile orc_union16 var42;
#else
  orc_union16 var42;
#endif
  orc_int8 var43;
  orc_union16 var44;
  orc_union16 var45;
  orc_union16 var46;
  orc_union16 var47;
  orc_union16 var48;
  orc_union16 var49;
  orc_union16 var50;
  orc_union16 var51;
  orc_union16 var52;
  orc_union16 var53;
  orc_union16 var54;
  orc_union16 var55;
  orc_union16 var56;

  ptr0 = (orc_int8 *)ex->arrays[0];
  ptr4 = (orc_int8 *)ex->arrays[4];
  ptr5 = (orc_int8 *)ex->arrays[5];
  ptr6 = (orc_int8 *)ex->arrays[6];
  ptr7 = (orc_int8 *)ex->arrays[7];


    var35.i = ex->params[24];

    var37.i = ex->params[25];

    var39.i = ex->params[26];

    var41.i = ex->params[27];

    var42.i = (int)0x00000020;

  for (i = 0; i < n; i++) {

    var34 = ptr4[i];

    var44.i = (orc_uint8)var34;

    var45.i = (var44.i * var35.i) & 0xffff;

    var36 = ptr5[i];

    var46.i = (orc_uint8)var36;

    var47.i = (var46.i * var37.i) & 0xffff;

    var48.i = var45.i + var47.i;

    var38 = ptr6[i];

    var49.i = (orc_uint8)var38;

    var50.i = (var49.i * var39.i) & 0xffff;

    var51.i = var48.i + var50.i;

    var40 = ptr7[i];

    var52.i = (orc_uint8)var40;

    var53.i = (var52.i * var41.i) & 0xffff;

    var54.i = var51.i + var53.i;

    var55.i = var54.i + var42.i;

    var56.i = var55.i >> 6;

    var43 = ORC_CLAMP_UB(var56.i);

    ptr0[i] = var43;
  }

}
