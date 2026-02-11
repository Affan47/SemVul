ngp_delete_extver_tab(void)
 { int i;

   if ((NULL == ngp_extver_tab) && (ngp_extver_tab_size > 0)) return(NGP_BAD_ARG);
   if ((NULL != ngp_extver_tab) && (ngp_extver_tab_size <= 0)) return(NGP_BAD_ARG);
   if ((NULL == ngp_extver_tab) && (0 == ngp_extver_tab_size)) return(NGP_OK);

   for (i=0; i<ngp_extver_tab_size; i++)
    { if (NULL != ngp_extver_tab[i].extname)
        { ngp_free(ngp_extver_tab[i].extname);
          ngp_extver_tab[i].extname = NULL;
        }
      ngp_extver_tab[i].version = 0;
    }
   ngp_free(ngp_extver_tab);
   ngp_extver_tab = NULL;
   ngp_extver_tab_size = 0;
   return(NGP_OK);
 }
