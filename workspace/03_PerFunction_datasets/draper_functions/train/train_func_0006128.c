ap_box1_clear(ap_box1_t* box)
{
  if (box->env==NULL){
    fprintf(stderr,"abstract1.c: box_clear: either non initialized or already deallocated box !\n");
    abort();
  }
  ap_interval_array_free(box->p,box->env->intdim+box->env->realdim);
  ap_environment_free(box->env);
  box->p=NULL;
  box->env=NULL;
}
