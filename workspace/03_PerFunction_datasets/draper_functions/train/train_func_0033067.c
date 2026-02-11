readDataFromClient(int pSock, struct shairbuffer *pClientBuffer)
{
  char tReadBuf[MAX_SIZE];
  tReadBuf[0] = '\0';

  int tRetval = 1;
  int tEnd = -1;
  while(tRetval > 0 && tEnd < 0)
  {

      slog(LOG_DEBUG_V, "Waiting To Read...\n");
      fflush(stdout);
      tRetval = read(pSock, tReadBuf, MAX_SIZE);

      tEnd = findEnd(tReadBuf);
      if(tEnd >= 0)
      {
        if(pClientBuffer->marker == 0)
        {
          pClientBuffer->marker = tEnd+1;
        }
        slog(SOCKET_LOG_LEVEL, "Found end of http request at: %d\n", tEnd);
        fflush(stdout);
      }
      else
      {
        tEnd = MAX_SIZE;
        slog(SOCKET_LOG_LEVEL, "Read %d of data so far\n%s\n", tRetval, tReadBuf);
        fflush(stdout);
      }
      if(tRetval > 0)
      {

        slog(SOCKET_LOG_LEVEL, "Read %d data, using %d of it\n", tRetval, tEnd);
        addNToShairBuffer(pClientBuffer, tReadBuf, tRetval);
        slog(LOG_DEBUG_VV, "Finished copying data\n");
      }
      else
      {
        slog(LOG_DEBUG, "Error reading data from socket, got: %d bytes", tRetval);
        return tRetval;
      }
  }
  if(tEnd + 1 != tRetval)
  {
    slog(SOCKET_LOG_LEVEL, "Read more data after end of http request. %d instead of %d\n", tRetval, tEnd+1);
  }
  slog(SOCKET_LOG_LEVEL, "Finished Reading Data:\n%s\nEndOfData\n", pClientBuffer->data);
  fflush(stdout);
  return 0;
}
