requestblock(int arrayno, int blocknumber, int blkndx, int size,
           int source,
           MPI_Request *request, MPI_Comm *comm)
{
    static int tag;
    int i, ierr;
    double *t;
    MPI_Status status;

    if (source==myrank)
    {
        *request=MPI_REQUEST_NULL;
        return;
    }


    t = c_get_block_data_addr(arrayno, blocknumber, blkndx);
    if (!t)
    {
       printf("Error: requestblock is unable to find arrayno, blocknumber %d %d/n", arrayno, blocknumber);
       MPI_Abort(MPI_COMM_WORLD, 0);
    }

    tag = form_msg_tag();

    MPI_Irecv(t, size, MPI_DOUBLE, source, tag, *comm, request);


    i = find_available_msg_buffer();
    msgbuf[i][0]=msggett;
    msgbuf[i][1]=arrayno;
    msgbuf[i][2]=blocknumber;
    msgbuf[i][3] = tag;
    msgbuf[i][4] = size;
    MPI_Isend(msgbuf[i], 5, MPI_INT, source, readytag, *comm,
              &ready_request[i]);
    nmessage_count++;
}
