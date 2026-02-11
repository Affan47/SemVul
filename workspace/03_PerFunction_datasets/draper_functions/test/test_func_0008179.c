_backup_gst_videoscale_orc_merge_bicubic_u8 (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int n = ex->n;
  orc_int8 * ORC_RESTRICT ptr0;
  const orc_int8 * ORC_RESTRICT ptr4;
  const orc_int8 * ORC_RESTRICT ptr5;
  const orc_int8 * ORC_RESTRICT ptr6;
  const orc_int8 * ORC_RESTRICT ptr7;
  orc_int8 var34;
  orc_int8 var35;
  orc_int8 var36;
  orc_int8 var37;
  orc_int8 var38;
  orc_int8 var39;
  orc_int8 var40;
  orc_int8 var41;
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

  ptr0 = (orc_int8 *)ex->arrays[0];
  ptr4 = (orc_int8 *)ex->arrays[4];
  ptr5 = (orc_int8 *)ex->arrays[5];
  ptr6 = (orc_int8 *)ex->arrays[6];
  ptr7 = (orc_int8 *)ex->arrays[7];


    var35 = ex->params[25];

    var37 = ex->params[26];

    var39 = ex->params[24];

    var41 = ex->params[27];

    var42.i = (int)0x00000020;

  for (i = 0; i < n; i++) {

    var34 = ptr5[i];

    var44.i = ((orc_uint8)var34) * ((orc_uint8)var35);

    var36 = ptr6[i];

    var45.i = ((orc_uint8)var36) * ((orc_uint8)var37);

    var46.i = var44.i + var45.i;

    var38 = ptr4[i];

    var47.i = ((orc_uint8)var38) * ((orc_uint8)var39);

    var48.i = var46.i - var47.i;

    var40 = ptr7[i];

    var49.i = ((orc_uint8)var40) * ((orc_uint8)var41);

    var50.i = var48.i - var49.i;

    var51.i = var50.i + var42.i;

    var52.i = var51.i >> 6;

    var43 = ORC_CLAMP_UB(var52.i);

    ptr0[i] = var43;
  }

}
