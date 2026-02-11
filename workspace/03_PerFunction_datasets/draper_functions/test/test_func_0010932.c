sq_create_from(const char *name, const char *desc, const char *acc)
{
  ESL_SQ *sq = NULL;
  int64_t n;
  int     status;

  ESL_ALLOC(sq, sizeof(ESL_SQ));
  sq->name   = NULL;
  sq->acc    = NULL;
  sq->desc   = NULL;
  sq->seq    = NULL;
  sq->dsq    = NULL;
  sq->ss     = NULL;

  if (name != NULL)
    {
      n = strlen(name)+1;
      ESL_ALLOC(sq->name, sizeof(char) * n);
      strcpy(sq->name, name);
      sq->nalloc = n;
    }
  else
    {
      sq->nalloc = eslSQ_NAMECHUNK;
      ESL_ALLOC(sq->name, sizeof(char) * sq->nalloc);
      sq->name[0] = '\0';
    }

  if (desc != NULL)
    {
      n = strlen(desc)+1;
      ESL_ALLOC(sq->desc, sizeof(char) * n);
      strcpy(sq->desc, desc);
      sq->dalloc = n;
    }
  else
    {
      sq->dalloc   = eslSQ_DESCCHUNK;
      ESL_ALLOC(sq->desc, sizeof(char) * sq->dalloc);
      sq->desc[0] = '\0';
    }

  if (acc != NULL)
    {
      n = strlen(acc)+1;
      ESL_ALLOC(sq->acc, sizeof(char) * n);
      strcpy(sq->acc, acc);
      sq->aalloc = n;
    }
  else
    {
      sq->aalloc   = eslSQ_ACCCHUNK;
      ESL_ALLOC(sq->acc,  sizeof(char) * sq->aalloc);
      sq->acc[0] = '\0';
    }


  sq->srcalloc = eslSQ_NAMECHUNK;
  ESL_ALLOC(sq->source, sizeof(char) * sq->srcalloc);
  sq->source[0] = '\0';


  sq->nxr    = 0;
  sq->xr_tag = NULL;
  sq->xr     = NULL;


  sq->doff = -1;
  sq->hoff = -1;
  sq->roff = -1;
  sq->eoff = -1;
  return sq;

 ERROR:
  esl_sq_Destroy(sq);
  return NULL;
}
