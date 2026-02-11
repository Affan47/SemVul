_backup_video_convert_orc_convert_UYVY_YUY2 (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int j;
  int n = ex->n;
  int m = ex->params[ORC_VAR_A1];
  orc_union32 * ORC_RESTRICT ptr0;
  const orc_union32 * ORC_RESTRICT ptr4;
  orc_union32 var32;
  orc_union32 var33;

  for (j = 0; j < m; j++) {
    ptr0 = ORC_PTR_OFFSET(ex->arrays[0], ex->params[0] * j);
    ptr4 = ORC_PTR_OFFSET(ex->arrays[4], ex->params[4] * j);


    for (i = 0; i < n; i++) {

      var32 = ptr4[i];

      var33.x2[0] = ORC_SWAP_W(var32.x2[0]);
      var33.x2[1] = ORC_SWAP_W(var32.x2[1]);

      ptr0[i] = var33;
    }
  }

}
