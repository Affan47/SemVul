_backup_orc_process_int8 (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int n = ex->n;
  orc_int8 * ORC_RESTRICT ptr0;
  orc_int8 var33;
  orc_int8 var34;
  orc_int8 var35;
  orc_union16 var36;
  orc_union16 var37;

  ptr0 = (orc_int8 *)ex->arrays[0];


    var34 = ex->params[24];

  for (i = 0; i < n; i++) {

    var33 = ptr0[i];

    var36.i = var33 * var34;

    var37.i = var36.i >> 3;

    var35 = var37.i;

    ptr0[i] = var35;
  }

}
