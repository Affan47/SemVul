vhx_initfig (pt_lkdfig, fp)

struct lkdfig *pt_lkdfig;
FILE          *fp       ;

  {
  struct simsig *pt_simsig = pt_lkdfig->SIMSIG;
  struct bussig *pt_bussig = pt_lkdfig->BUSSIG;
  struct lkdins *pt_lkdins = pt_lkdfig->LKDINS;
  struct wrireg *pt_wrireg ;
  struct wriaux *pt_wriaux ;
  struct wribux *pt_wribux ;
  struct prjbvl *pt_prjbvl ;
  struct prjrvl *pt_prjrvl ;
  unsigned int   size      ;
  char          *pt_mem    ;
  char           errflg    = 0;


  vhx_getsize (pt_lkdfig);


  fread (&size, sizeof (unsigned int), 1, fp);
  if (size != pt_lkdfig->VALSIZ)
    {
    errflg = vhu_error (115, NULL, NULL);
    }
  else
    {


    while (pt_simsig != NULL)
      {
      pt_simsig->PRJVAL    = fgetc (fp);
      *(pt_simsig->CURVAL) = fgetc (fp);
      pt_simsig            = pt_simsig->NEXT;
      }

    while (pt_bussig != NULL)
      {
      pt_prjbvl = pt_bussig->PRJBVL;
      while (pt_prjbvl != NULL)
        {
        pt_prjbvl->DRVVAL = fgetc (fp);
        pt_prjbvl->CNDVAL = fgetc (fp);
        pt_prjbvl         = pt_prjbvl->GLNEXT;
        }
      *(pt_bussig->CURVAL) = fgetc (fp);
      pt_bussig = pt_bussig->NEXT;
      }


    while (pt_lkdins != NULL)
      {
      if (pt_lkdins->FLAG == VHL_CMODEL)
        {
        size = vhx_getvalu (pt_lkdins, &pt_mem, 0);
        fread (pt_mem, sizeof (char), size, fp);
        }
      else
        {
        pt_wrireg = pt_lkdins->WRIREG;
        pt_wriaux = pt_lkdins->WRIAUX;
        pt_wribux = pt_lkdins->WRIBUX;

        while (pt_wrireg != NULL)
          {
          pt_prjrvl = pt_wrireg->PRJRVL;
          while (pt_prjrvl != NULL)
            {
            pt_prjrvl->DRVVAL = fgetc (fp);
            pt_prjrvl->CNDVAL = fgetc (fp);
            pt_prjrvl         = pt_prjrvl->NEXT;
            }
          *(pt_wrireg->CURVAL) = fgetc (fp);
          pt_wrireg = pt_wrireg->NEXT;
          }

        while (pt_wribux != NULL)
          {
          pt_prjbvl = pt_wribux->PRJBVL;
          while (pt_prjbvl != NULL)
            {
            pt_prjbvl->DRVVAL = fgetc (fp);
            pt_prjbvl->CNDVAL = fgetc (fp);
            pt_prjbvl         = pt_prjbvl->NEXT;
            }
          *(pt_wribux->CURVAL) = fgetc (fp);
          pt_wribux = pt_wribux->NEXT;
          }

        while (pt_wriaux != NULL)
          {
          pt_wriaux->PRJVAL    = fgetc (fp);
          *(pt_wriaux->CURVAL) = fgetc (fp);
          pt_wriaux            = pt_wriaux->NEXT;
          }
        }

      pt_lkdins = pt_lkdins->NEXT;
      }
    }
  return (errflg);
  }
