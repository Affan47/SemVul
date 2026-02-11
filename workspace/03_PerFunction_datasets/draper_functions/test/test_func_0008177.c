writeOperandWithCast(Value* Operand, unsigned Opcode) {


  Type* OpTy = Operand->getType();


  bool shouldCast = false;


  bool castIsSigned = false;


  switch (Opcode) {
    default:

      break;
    case Instruction::Add:
    case Instruction::Sub:
    case Instruction::Mul:


    case Instruction::LShr:
    case Instruction::UDiv:
    case Instruction::URem:
      shouldCast = true;
      castIsSigned = false;
      break;
    case Instruction::GetElementPtr:
    case Instruction::AShr:
    case Instruction::SDiv:
    case Instruction::SRem:
      shouldCast = true;
      castIsSigned = true;
      break;
  }


  if (shouldCast) {
    Out << "((";
    printSimpleType(Out, OpTy, castIsSigned);
    Out << ")";
    writeOperand(Operand);
    Out << ")";
  } else
    writeOperand(Operand);
}
