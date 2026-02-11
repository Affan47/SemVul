BraState_Init(void *pp)
{
  CBraState *p = ((CBraState *)pp);
  p->bufPos = p->bufConv = p->bufTotal = 0;
  x86_Convert_Init(p->x86State);
  if (p->methodId == XZ_ID_Delta)
    Delta_Init(p->deltaState);
}
