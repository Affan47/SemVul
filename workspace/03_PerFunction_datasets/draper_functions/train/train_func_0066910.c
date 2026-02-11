IsEmpty()
{
  int count = 0;
  for(int i =0; i < 64; i++)
    {
    vtkDebugLeaksHashNode *pos = this->Nodes[i];
    if(pos)
      {
      if(!vtkDebugLeaksIgnoreClassesCheck(pos->Key))
        {
        count += pos->Count;
        }
      while(pos->Next)
        {
        pos = pos->Next;
        if(!vtkDebugLeaksIgnoreClassesCheck(pos->Key))
          {
          count += pos->Count;
          }
        }
      }
    }
  return !count;
}
