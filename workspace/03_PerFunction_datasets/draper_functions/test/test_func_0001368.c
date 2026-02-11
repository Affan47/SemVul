_backup_gst_videoscale_orc_resample_bilinear_u32 (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int n = ex->n;
  orc_union32 * ORC_RESTRICT ptr0;
  const orc_union32 * ORC_RESTRICT ptr4;
  orc_union32 var32;

  ptr0 = (orc_union32 *)ex->arrays[0];
  ptr4 = (orc_union32 *)ex->arrays[4];


  for (i = 0; i < n; i++) {

    {
    int tmp = ex->params[24] + i * ex->params[25];
    orc_union32 a = ptr4[tmp>>16];
    orc_union32 b = ptr4[(tmp>>16)+1];
    var32.x4[0] = ((orc_uint8)a.x4[0] * (256-((tmp>>8)&0xff)) + (orc_uint8)b.x4[0] * ((tmp>>8)&0xff))>>8;
    var32.x4[1] = ((orc_uint8)a.x4[1] * (256-((tmp>>8)&0xff)) + (orc_uint8)b.x4[1] * ((tmp>>8)&0xff))>>8;
    var32.x4[2] = ((orc_uint8)a.x4[2] * (256-((tmp>>8)&0xff)) + (orc_uint8)b.x4[2] * ((tmp>>8)&0xff))>>8;
    var32.x4[3] = ((orc_uint8)a.x4[3] * (256-((tmp>>8)&0xff)) + (orc_uint8)b.x4[3] * ((tmp>>8)&0xff))>>8;
    }

    ptr0[i] = var32;
  }

}
