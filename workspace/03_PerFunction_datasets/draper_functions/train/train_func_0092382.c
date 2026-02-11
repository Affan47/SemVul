free_info_weak(info_weak *i_weak)
{
  if ( i_weak->nweak > 0 ) {
    free(i_weak->var);
    free(i_weak->type);
  }
  free(i_weak);
}
