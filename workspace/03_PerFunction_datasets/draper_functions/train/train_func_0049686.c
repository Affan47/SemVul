tryParseRegister() {
  const AsmToken &Tok = Parser.getTok();
  if (Tok.isNot(AsmToken::Identifier)) return -1;


  std::string upperCase = Tok.getString().str();
  std::string lowerCase = LowercaseString(upperCase);
  unsigned RegNum = MatchRegisterName(lowerCase);
  if (!RegNum) {
    RegNum = StringSwitch<unsigned>(lowerCase)
      .Case("r13", ARM::SP)
      .Case("r14", ARM::LR)
      .Case("r15", ARM::PC)
      .Case("ip", ARM::R12)
      .Default(0);
  }
  if (!RegNum) return -1;

  Parser.Lex();

#if 0


  if (Parser.getTok().is(AsmToken::LBrac)) {
    SMLoc SIdx = Parser.getTok().getLoc();
    Parser.Lex();

    const MCExpr *ImmVal;
    if (getParser().ParseExpression(ImmVal))
      return MatchOperand_ParseFail;
    const MCConstantExpr *MCE = dyn_cast<MCConstantExpr>(ImmVal);
    if (!MCE) {
      TokError("immediate value expected for vector index");
      return MatchOperand_ParseFail;
    }

    SMLoc E = Parser.getTok().getLoc();
    if (Parser.getTok().isNot(AsmToken::RBrac)) {
      Error(E, "']' expected");
      return MatchOperand_ParseFail;
    }

    Parser.Lex();

    Operands.push_back(ARMOperand::CreateVectorIndex(MCE->getValue(),
                                                     SIdx, E,
                                                     getContext()));
  }
#endif

  return RegNum;
}
