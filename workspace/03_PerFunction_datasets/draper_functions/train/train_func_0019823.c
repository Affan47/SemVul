exchange_same(char *sendbuf, char *recvbuf)
{


  int recvoffset = 0;
  for (int irecv = 0; irecv < nrecv; irecv++) {
    MPI_Irecv(&recvbuf[recvoffset],recvsize[irecv],MPI_BYTE,
            recvproc[irecv],0,comm,&request[irecv]);
    recvoffset += recvsize[irecv];
  }


  char *buf = (char *) memory->smalloc(nsendmax,"buf");


  MPI_Barrier(comm);


  int m = 0;
  for (int isend = 0; isend < nsend; isend++) {
    int bufoffset = 0;
    for (int i = 0; i < sendcount[isend]; i++) {
      memcpy(&buf[bufoffset],&sendbuf[nsize*sendindices[m++]],nsize);
      bufoffset += nsize;
    }
    MPI_Send(buf,sendsize[isend],MPI_BYTE,sendproc[isend],0,comm);
  }


  if (self)
    for (int i = 0; i < sendcount[nsend]; i++) {
      memcpy(&recvbuf[recvoffset],&sendbuf[nsize*sendindices[m++]],nsize);
      recvoffset += nsize;
    }


  memory->sfree(buf);


  if (nrecv) MPI_Waitall(nrecv,request,status);
}
