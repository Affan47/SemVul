MPI_Allgatherv(void *sendbuf, int sendcount, MPI_Datatype sendtype,
        void *recvbuf, int * , int * ,
        MPI_Datatype , MPI_Comm )
{
  int n = 0;
  if (sendtype == MPI_INT) n = sendcount*sizeof(int);
  else if (sendtype == MPI_FLOAT) n = sendcount*sizeof(float);
  else if (sendtype == MPI_DOUBLE) n = sendcount*sizeof(double);
  else if (sendtype == MPI_CHAR) n = sendcount*sizeof(char);
  else if (sendtype == MPI_BYTE) n = sendcount*sizeof(char);
  else if (sendtype == MPI_DOUBLE_INT) n = sendcount*sizeof(double_int);

  memcpy(recvbuf,sendbuf,n);
}
