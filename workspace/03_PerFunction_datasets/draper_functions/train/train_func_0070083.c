vhx_muxpubit (pt_prjbvl)

struct prjbvl *pt_prjbvl;

  {
  char resval      = '1';
  int  active_driv = 0  ;
  int  unknown_driv = 0  ;

  while (pt_prjbvl != NULL)
    {
    if (pt_prjbvl->CNDVAL == '1')
      {
      resval = pt_prjbvl->DRVVAL;
      active_driv++;
      }
    else
      {
      if (pt_prjbvl->CNDVAL == 'u')
        {
        resval = pt_prjbvl->DRVVAL;
        unknown_driv++;
        }
      }

    pt_prjbvl = pt_prjbvl->GLNEXT;
    }

  if ((active_driv + unknown_driv) > 1)
    resval = 'u';

  return (resval);
  }
