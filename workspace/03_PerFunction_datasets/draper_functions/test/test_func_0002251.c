CheckMult(infoexpressao term, int op, infoexpressao factor){
  infoexpressao res;
  res.opnd.tipo = INVALOPND;

  switch(op) {
    case MULT:
    case DIV:
      if( (term.tipo != INTEIRO && term.tipo != REAL && term.tipo != CARACTERE) || (factor.tipo != INTEIRO && factor.tipo != REAL && factor.tipo != CARACTERE) )
        OperandoNaoAritmetico();

      if(term.tipo == REAL || factor.tipo == REAL) res.tipo = REAL;
      else res.tipo = INTEIRO;

      res.opnd.tipo = VAROPND;
      res.opnd.atr.simb = NovaTemp(res.tipo);

      switch (op) {
        case MULT:
          GeraQuadrupla(OPMULT, term.opnd, factor.opnd, res.opnd);
          break;
        case DIV:
          GeraQuadrupla(OPDIV, term.opnd, factor.opnd, res.opnd);
          break;
      }
      break;

    case RESTO:
      if(term.tipo != INTEIRO && term.tipo != CARACTERE || factor.tipo != INTEIRO && factor.tipo != CARACTERE)
        OperandoInvalidoAoResto();
      res.tipo = INTEIRO;
      res.opnd.tipo = VAROPND;
      res.opnd.atr.simb = NovaTemp(res.tipo);
      GeraQuadrupla(OPRESTO, term.opnd, factor.opnd, res.opnd);
      break;

  }
  return res;
}
