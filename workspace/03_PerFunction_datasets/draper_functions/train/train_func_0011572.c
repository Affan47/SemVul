GetNumberOfThreads()
{
  int num = this->NumberOfThreads;
  if(vtkMultiThreaderGlobalMaximumNumberOfThreads > 0 &&
     num > vtkMultiThreaderGlobalMaximumNumberOfThreads)
    {
    num = vtkMultiThreaderGlobalMaximumNumberOfThreads;
    }
  return num;
}
