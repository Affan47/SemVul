Process(float_buff *Input)
{ int err,i,o; float *Inp,*Out; int InpLen;
  Inp=Input->Data; InpLen=Input->Len;
  err=Output.EnsureSpace((int)ceil(InpLen/OutStep)+2); if(err) return err;
  Out=Output.Data;
  for(o=0; OutPhase<0; )
  { Out[o++]=Inp[0]*(1.0+OutPhase)-OutPhase*PrevSample; OutPhase+=OutStep; }
  for(i=0; i<(InpLen-1); )
  { if(OutPhase>=1.0) { OutPhase-=1.0; i++; }
    else { Out[o++]=Inp[i]*(1.0-OutPhase)+Inp[i+1]*OutPhase;
	   OutPhase+=OutStep; }
  } Output.Len=o; PrevSample=Inp[i]; OutPhase-=1.0;
  return 0;
}
