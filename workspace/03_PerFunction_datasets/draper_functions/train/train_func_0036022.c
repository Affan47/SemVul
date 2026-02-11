XMPI_Coloron(int red, int green, int blue)
{
  lam_initerr();
  lam_setfunc(BLKXMPICOLORON);

  if (red < 0 || red > 255 || green < 0 || green > 255 ||
      blue < 0 || blue > 255)
    return(lam_errfunc(MPI_COMM_WORLD,
		       lam_getfunc(), lam_mkerr(MPI_ERR_ARG, EINVAL)));


  if (LAM_TRACE_TOP())
    if (lam_tr_coloron(red, green, blue, MPI_Wtime()) != 0)
      return(lam_errfunc(MPI_COMM_WORLD,
			 lam_getfunc(), lam_mkerr(MPI_ERR_INTERN, EINVAL)));

  lam_resetfunc(BLKXMPICOLORON);
  return MPI_SUCCESS;
}
