PrintImmediateOp(byte* data) {
  bool byte_size_immediate = (*data & 0x02) != 0;
  byte modrm = *(data + 1);
  int mod, regop, rm;
  get_modrm(modrm, &mod, &regop, &rm);
  const char* mnem = "Imm???";
  switch (regop) {
    case 0:
      mnem = "add";
      break;
    case 1:
      mnem = "or";
      break;
    case 2:
      mnem = "adc";
      break;
    case 4:
      mnem = "and";
      break;
    case 5:
      mnem = "sub";
      break;
    case 6:
      mnem = "xor";
      break;
    case 7:
      mnem = "cmp";
      break;
    default:
      UnimplementedInstruction();
  }
  AppendToBuffer("%s%c ", mnem, operand_size_code());
  int count = PrintRightOperand(data + 1);
  AppendToBuffer(",0x");
  OperandSize immediate_size = byte_size_immediate ? BYTE_SIZE : operand_size();
  count += PrintImmediate(data + 1 + count, immediate_size);
  return 1 + count;
}
