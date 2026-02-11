ap_dimchange_fprint(FILE* stream, ap_dimchange_t* dimchange)
{
  size_t i;

  fprintf(stream,"dimchange: intdim=%lu, realdim=%lu\n           ",
	  (unsigned long)dimchange->intdim,
	  (unsigned long)dimchange->realdim);
  for (i=0;i<dimchange->intdim+dimchange->realdim;i++){
    fprintf(stream,"%2lu ",(unsigned long)dimchange->dim[i]);
  }
  fprintf(stream,"\n");
}
