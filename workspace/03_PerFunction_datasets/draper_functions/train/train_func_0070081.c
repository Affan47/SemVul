toIR (IRState *irs)
{
  if (statement)
    {
      irs->startScope();
      statement->toIR (irs);
      irs->endScope();
    }
}
