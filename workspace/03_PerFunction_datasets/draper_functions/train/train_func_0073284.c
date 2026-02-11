set_rectify_kernel_type( xsh_rectify_param *recpar )
{
  const XSH_KERNEL_TYPE * pk = xsh_ker_type ;

  for( ; pk->name != NULL ; pk++ )
    if ( strcasecmp( recpar->rectif_kernel, pk->name ) == 0 ) {
      recpar->kernel_type = pk->type ;
      return ;
    }
  recpar->kernel_type = CPL_KERNEL_DEFAULT ;

  return ;
}
