WriteBaseTransitionMatrices_t(int t, FILE *f, char *filename, char *header, TStateModel *model)
{
  FILE *f_out;
  int rtrn=0;
  if (sv_ComputeTransitionMatrix(t,model->sv,model))
    {
      f_out=f ? f : filename ? fopen(filename,"at") : (FILE*)NULL;
      rtrn=(f_out) ? sv_WriteBaseTransitionMatrices(f_out,model->sv,header,"") : 0;
      if (!f && f_out) fclose(f_out);
    }
  return rtrn;
}
