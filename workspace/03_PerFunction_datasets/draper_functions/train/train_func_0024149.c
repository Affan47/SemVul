log()
{
  if(log_file) {
    unsigned int i;
    for(i=0; i<trace.trace_index; i++)
      fprintf(log_file,"%08X\n",trace[i]);

    trace.trace_index = 0;
  }

}
