gap_stb_syntax_get_parname_idx(const char *record_key
                 ,const char *parname
                 )
{
  GapStbSyntaxElem  *sp_elem;

  if(global_syntax_par_list == NULL)
  {
    p_create_syntax_list();
  }

  if((record_key == NULL)
  || (parname == NULL))
  {
    return(-1);
  }


  for(sp_elem = global_syntax_par_list; sp_elem != NULL; sp_elem = (GapStbSyntaxElem  *)sp_elem->next)
  {
    if(strcmp(record_key, sp_elem->record_key) == 0)
    {
      GapStbSyntaxParElem *par;

      for(par=sp_elem->par_list; par != NULL; par = (GapStbSyntaxParElem *)par->next)
      {
        if(strcmp(par->parname, parname) == 0)
        {
          return(par->par_idx);
        }
      }
      return(-1);
    }
  }
  return(-1);
}
