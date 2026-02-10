kwsysProcessClosePipes(kwsysProcess* cp)
{
  int i;


  for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
    {
    if(cp->PipeReadEnds[i] >= 0)
      {
#if KWSYSPE_USE_SELECT


      if(FD_ISSET(cp->PipeReadEnds[i], &cp->PipeSet))
        {

        FD_CLR(cp->PipeReadEnds[i], &cp->PipeSet);


        while((read(cp->PipeReadEnds[i], cp->PipeBuffer,
                    KWSYSPE_PIPE_BUFFER_SIZE) < 0) && (errno == EINTR));
        }
#endif


      kwsysProcessCleanupDescriptor(&cp->PipeReadEnds[i]);
      --cp->PipesLeft;
      }
    }
}
