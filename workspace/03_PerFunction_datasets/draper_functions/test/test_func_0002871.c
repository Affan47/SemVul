vhl_makgst (pt_befig)

struct befig *pt_befig;

  {
  struct chain *name_lst       ;
  struct locon *pt_locon       ;
  struct bepor *pt_bepor       ;
  struct lofig *pt_lofig       ;
  struct loins *pt_loins       ;
  struct losig *pt_losig       ;
  int           index          = 0;
  char          lofigname [80] ;

  sprintf (lofigname, "root_of_%s", pt_befig->NAME);
  pt_lofig = addlofig (lofigname);

  pt_loins = (struct loins *) vhu_alloc (sizeof(struct loins), VHU_ALIGN);

  pt_loins->INSNAME = pt_befig->NAME;
  pt_loins->FIGNAME = pt_befig->NAME;
  pt_loins->LOCON   = NULL;
  pt_loins->USER    = NULL;
  pt_loins->NEXT    = NULL;

  pt_lofig->LOINS = pt_loins;

  pt_bepor = pt_befig->BEPOR;
  while (pt_bepor != NULL)
    {
    name_lst      = addchain (NULL    , pt_bepor->NAME);
    pt_losig      = addlosig (pt_lofig, index, name_lst, 'E');

    if (pt_bepor->TYPE != 'B')
      pt_losig->USER = addptype (pt_losig->USER, pt_bepor->TYPE, NULL);

    pt_locon            = (struct locon *)
                          vhu_alloc (sizeof(struct locon), VHU_ALIGN);
    pt_locon->NAME      = pt_bepor->NAME     ;
    pt_locon->SIG       = pt_losig           ;
    pt_locon->ROOT      = (void *) pt_lofig  ;
    pt_locon->DIRECTION = pt_bepor->DIRECTION;
    pt_locon->TYPE      = 'E'                ;
    pt_locon->USER      = NULL               ;
    pt_locon->NEXT      = pt_lofig->LOCON    ;
    pt_lofig->LOCON     = pt_locon           ;

    pt_locon            = (struct locon *)
                          vhu_alloc (sizeof(struct locon), VHU_ALIGN);
    pt_locon->NAME      = pt_bepor->NAME     ;
    pt_locon->SIG       = pt_losig           ;
    pt_locon->ROOT      = (void *) pt_loins  ;
    pt_locon->DIRECTION = pt_bepor->DIRECTION;
    pt_locon->TYPE      = 'I'                ;
    pt_locon->USER      = NULL               ;
    pt_locon->NEXT      = pt_loins->LOCON    ;
    pt_loins->LOCON     = pt_locon           ;

    pt_bepor = pt_bepor->NEXT;
    index ++;
    }
  pt_lofig->LOCON = (struct locon *) reverse ((struct chain *) pt_lofig->LOCON);
  pt_loins->LOCON = (struct locon *) reverse ((struct chain *) pt_loins->LOCON);

  return (pt_lofig);
  }
