CoreProc(fcmpx x[])
{ int Groups,GroupHalfSize,Group,Bf,TwidIdx;
  int HalfSize=Size/2;
  for(Bf=0; Bf<Size; Bf+=2) FFT2(x[Bf],x[Bf+1]);

  for(Groups=HalfSize/2,GroupHalfSize=2; Groups; Groups>>=1, GroupHalfSize<<=1)
    for(Group=0,Bf=0; Group<Groups; Group++,Bf+=GroupHalfSize)
      for(TwidIdx=0; TwidIdx<HalfSize; TwidIdx+=Groups,Bf++)
      { FFTbf(x[Bf],x[Bf+GroupHalfSize],Twiddle[TwidIdx]);
	 }
}
