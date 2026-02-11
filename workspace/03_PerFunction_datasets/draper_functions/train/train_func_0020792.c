Check_Input_Range( int val, int lo, int hi, char *message, MPI_Comm comm )
{
  if( val < lo || val > hi ) {
    fprintf( stderr, "%s\nInput %d - Out of range %d-%d. Terminating...\n",
             message, val, lo, hi );
    MPI_Abort( comm, INVALID_INPUT );
  }

  return 1;
}
