boundary_mpi_read (GtsObject ** o, GtsFile * fp)
{
  if (fp->type == GTS_INT) {
    GFS_BOUNDARY_MPI (*o)->process = atoi (fp->token->str);
    gts_file_next_token (fp);
    if (fp->type != GTS_INT) {
      gts_file_error (fp, "expecting an integer (id)");
      return;
    }
    GFS_BOUNDARY_MPI (*o)->id = atoi (fp->token->str);
    gts_file_next_token (fp);
  }
  else
    GFS_BOUNDARY_MPI (*o)->process = GFS_BOUNDARY_MPI (*o)->id = -1;
}
