Process(float_buff *Input)
{ int err=Output.EnsureSpace(Input->Len); if(err) return -1;
  Process(Input->Data,Input->Len,Output.Data);
  Output.Len=Input->Len; return 0; }
