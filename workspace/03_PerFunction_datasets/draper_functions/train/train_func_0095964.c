ExecQuadAtrib(quadrupla quad) {
  int tipo1, valint1;
  float valfloat1;
  char valchar1, vallogic1;
  switch(quad->opnd1.tipo) {
    case INTOPND:
      tipo1 = INTOPND;
      valint1 = quad->opnd1.atr.valint; break;
    case REALOPND:
      tipo1 = REALOPND;
      valfloat1 = quad->opnd1.atr.valfloat; break;
    case CHAROPND:
      tipo1 = CHAROPND;
      valchar1 = quad->opnd1.atr.valchar; break;
    case LOGICOPND:
      tipo1 = LOGICOPND;
      vallogic1 = quad->opnd1.atr.vallogic; break;
    case VAROPND:
      switch (quad->opnd1.atr.simb->tvar) {
        case INTEIRO:
          tipo1 = INTOPND;
          valint1 = *(quad->opnd1.atr.simb->valint); break;
        case REAL:
          tipo1 = REALOPND;
          valfloat1=*(quad->opnd1.atr.simb->valfloat);break;
        case CARACTERE:
          tipo1 = CHAROPND;
          valchar1=*(quad->opnd1.atr.simb->valchar);break;
        case LOGICO:
          tipo1 = LOGICOPND;
          vallogic1 = *(quad->opnd1.atr.simb->vallogic);
          break;
      }
      break;
  }
  switch(quad->result.atr.simb->tvar) {
    case INTEIRO:
      if (tipo1 == INTOPND)  *(quad->result.atr.simb->valint) = valint1;
      if (tipo1 == CHAROPND) *(quad->result.atr.simb->valint) = valchar1;
      break;
    case CARACTERE:
      if (tipo1 == INTOPND)  *(quad->result.atr.simb->valchar) = valint1;
      if (tipo1 == CHAROPND) *(quad->result.atr.simb->valchar) = valchar1;
      break;
    case LOGICO:  *(quad->result.atr.simb->vallogic) = vallogic1; break;
    case REAL:
      if (tipo1 == INTOPND)
        *(quad->result.atr.simb->valfloat) = valint1;
      if (tipo1 == REALOPND)
        *(quad->result.atr.simb->valfloat) = valfloat1;
      if (tipo1 == CHAROPND)
        *(quad->result.atr.simb->valfloat) = valchar1;
      break;
  }
  printf("ATRIBUTED: %d", valint1);
}
