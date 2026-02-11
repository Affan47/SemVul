ExecQuadRead(quadrupla quad) {
  int i;  operando opndaux;
  pilhaoperando pilhaopndaux;

  printf("\n    Lendo: \n");
  InicPilhaOpnd(&pilhaopndaux);
  for (i = 1; i <= quad->opnd1.atr.valint; i++) {
    EmpilharOpnd(TopoOpnd (pilhaopnd), &pilhaopndaux);
    DesempilharOpnd(&pilhaopnd);
  }
  for (i = 1; i <= quad->opnd1.atr.valint; i++) {
    opndaux = TopoOpnd(pilhaopndaux);
    DesempilharOpnd (&pilhaopndaux);
        switch (opndaux.atr.simb->tvar) {
          case INTEIRO:
              fscanf(finput, "%d", opndaux.atr.simb->valint); printf("readed: %d\n", *opndaux.atr.simb->valint); break;
             case REAL:
              fscanf(finput, "%g", opndaux.atr.simb->valfloat); printf("readed: %g\n", *opndaux.atr.simb->valfloat); break;
            case LOGICO:
              fscanf(finput, "%d", opndaux.atr.simb->vallogic); printf("readed: %d\n", *opndaux.atr.simb->vallogic); break;
            case CARACTERE:
              fscanf(finput, "%c", opndaux.atr.simb->valchar); printf("readed: %c\n", *opndaux.atr.simb->valchar); break;
        }
  }
}
