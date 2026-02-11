create_comm_world(int num_procs, int *doing_pio)
{

    int     mrc;
    int     color;
    int     myrank, nprocs;

    pio_comm_g = MPI_COMM_NULL;


    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if (num_procs > nprocs) {
        fprintf(stderr,
                "number of process(%d) must be <= number of processes in MPI_COMM_WORLD(%d)\n",
                num_procs, nprocs);
        goto error_done;
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    color = (myrank < num_procs);
    mrc = MPI_Comm_split(MPI_COMM_WORLD, color, myrank, &pio_comm_g);

    if (mrc != MPI_SUCCESS) {
        fprintf(stderr, "MPI_Comm_split failed\n");
        goto error_done;
    }

    if (!color) {

        mrc = destroy_comm_world();
        goto done;
    }


    MPI_Comm_size(pio_comm_g, &pio_mpi_nprocs_g);
    MPI_Comm_rank(pio_comm_g, &pio_mpi_rank_g);

done:
    *doing_pio = color;
    return SUCCESS;

error_done:
    destroy_comm_world();
    return FAIL;
}
