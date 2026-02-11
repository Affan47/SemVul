eio_init
  (int& info)
{
  paraState.isParallel = 0;
  paraState.numProc    = 1;
  paraState.myProc     = 0;

  if(modelManager = new EIOModelManager)
    {
      info = 0;
    }
  else
    {
      info = -1;
    }
}
