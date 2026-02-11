mesh_resample_choose_aa_by_name(char * s)
{
  int f=0;
  while(resample_choices[f]) {
    if (0==strcmp (s,resample_array_inv_names[f]))
      {
	resample_array_inv=resample_choices[f];
	return;
      }
    f++;
  }

  fprintf(stderr,"\n%s:%d: no choice '%s' for kernel!\n",__FILE__,__LINE__,s);
}
