kwsysProcess_SetTimeout(kwsysProcess* cp, double timeout)
{
  if(!cp)
    {
    return;
    }
  cp->Timeout = timeout;
  if(cp->Timeout < 0)
    {
    cp->Timeout = 0;
    }
}
