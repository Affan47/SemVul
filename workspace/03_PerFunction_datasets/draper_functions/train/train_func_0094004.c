mpi_stats_dump()
{
  char* env_str = getenv("EZTRACE_MPI_DUMP_MESSAGES");

  if(env_str) {
    char* path;
    asprintf(&path, "%s/%s_eztrace_message_dump", eztrace_stats_get_output_dir(), getenv("USER"));
    FILE *f = fopen(path, "w");
    if(!f)
      perror("Error while dumping messages");

    __print_p2p_messages(f);
    int ret = fclose(f);
    if(ret)
      perror("Error while dumping messages (fclose)");

    printf("\n\tMPI messages dumped in %s\n", path);
    free(path);
  }
}
