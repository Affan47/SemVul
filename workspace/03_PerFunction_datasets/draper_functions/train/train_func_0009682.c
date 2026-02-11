end_of_step()
{
  bigint ntimestep = update->ntimestep;

  Output_ReaxC_Bonds(update->ntimestep,fp);
  if (me == 0) fflush(fp);
}
