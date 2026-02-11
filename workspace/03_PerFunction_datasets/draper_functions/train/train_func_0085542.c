FreeMat(fullmat_t *fullmat)
{
  if(fullmat->unpaired != NULL)
    {
      free(fullmat->unpaired->matrix);
      free(fullmat->unpaired);
    }
  if(fullmat->paired != NULL)
    {
      free(fullmat->paired->matrix);
      free(fullmat->paired);
    }
  if(fullmat->name != NULL)
    free(fullmat->name);
  if(fullmat->g != NULL)
    free(fullmat->g);
  free(fullmat);
}
