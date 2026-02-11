StackFromGUI(wc, wd)
ChimeraContext wc;
ChimeraGUI wd;
{
  ChimeraStack cs;

  for (cs = (ChimeraStack)GListGetHead(wc->cres->stacks); cs != NULL;
       cs = (ChimeraStack)GListGetNext(wc->cres->stacks))
  {
    if (cs->wd == wd) return(cs);
  }

  return(NULL);
}
