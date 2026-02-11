_backup_cogorc_getline_UYVY (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int n = ex->n;
  orc_union64 * ORC_RESTRICT ptr0;
  const orc_union32 * ORC_RESTRICT ptr4;
  orc_union32 var36;
#if defined(__APPLE__) && __GNUC__ == 4 && __GNUC_MINOR__ == 2 && defined (__i386__)
  volatile orc_union16 var37;
#else
  orc_union16 var37;
#endif
  orc_union64 var38;
  orc_union16 var39;
  orc_union16 var40;
  orc_union32 var41;
  orc_union32 var42;

  ptr0 = (orc_union64 *)ex->arrays[0];
  ptr4 = (orc_union32 *)ex->arrays[4];


    var37.x2[0] = (int)0x000000ff;
    var37.x2[1] = (int)0x000000ff;

  for (i = 0; i < n; i++) {

    var36 = ptr4[i];

    {
       orc_union16 _src;
       _src.i = var36.x2[0];
       var39.x2[0] = _src.x2[1];
       var40.x2[0] = _src.x2[0];
    }
    {
       orc_union16 _src;
       _src.i = var36.x2[1];
       var39.x2[1] = _src.x2[1];
       var40.x2[1] = _src.x2[0];
    }

    {
       orc_union16 _dest;
       _dest.x2[0] = var37.x2[0];
       _dest.x2[1] = var39.x2[0];
       var41.x2[0] = _dest.i;
    }
    {
       orc_union16 _dest;
       _dest.x2[0] = var37.x2[1];
       _dest.x2[1] = var39.x2[1];
       var41.x2[1] = _dest.i;
    }

    {
       orc_union32 _dest;
       _dest.x2[0] = var40.i;
       _dest.x2[1] = var40.i;
       var42.i = _dest.i;
    }

    {
       orc_union32 _dest;
       _dest.x2[0] = var41.x2[0];
       _dest.x2[1] = var42.x2[0];
       var38.x2[0] = _dest.i;
    }
    {
       orc_union32 _dest;
       _dest.x2[0] = var41.x2[1];
       _dest.x2[1] = var42.x2[1];
       var38.x2[1] = _dest.i;
    }

    ptr0[i] = var38;
  }

}
