stack_alu_const(int alu_op, int num)
{
  if (num > 65535 || num < -32768)
  {
    printf("Error: literal value %d bigger than 16 bit.\n", num);
    return -1;
  }

  fprintf(out, "  ;; stack_alu_const(%s, %d)\n", alu_str[alu_op], num);

  uint16_t value = (((int16_t)num) & 0xffff);

  if (value == 0 && alu_op <= ALU_SUB) { return 0; }
  if (value == 1 && alu_op == ALU_ADD)
  {
    fprintf(out, "  pop de\n");
    fprintf(out, "  inc de\n");
    fprintf(out, "  push de\n");
    return 0;
  }
  if (value == 1 && alu_op == ALU_SUB)
  {
    fprintf(out, "  pop de\n");
    fprintf(out, "  dec de\n");
    fprintf(out, "  push de\n");
    return 0;
  }

  if (alu_op <= ALU_SUB)
  {
#if 0
    fprintf(out, "  pop hl\n");
    fprintf(out, "  ld bc, %04x\n", value);


    fprintf(out, "  and a   ; clear carry\n");
    fprintf(out, "  %s hl, bc\n", alu_str[alu_op]);
    fprintf(out, "  push hl\n");
#endif
    fprintf(out, "  pop hl\n");
    fprintf(out, "  ld b, %04x\n", value >> 8);
    fprintf(out, "  ld c, %04x\n", value & 0xff);
    if (alu_op == ALU_SUB)
    {
      fprintf(out, "  and a   ; clear carry\n");
    }

    fprintf(out, "  %s hl, bc\n", alu_str[alu_op]);
    fprintf(out, "  push hl\n");
    return 0;
  }


  fprintf(out, "  pop hl\n");
  fprintf(out, "  ld a, h\n");
  fprintf(out, "  %s %02x\n", alu_str[alu_op], value >> 8);
  fprintf(out, "  ld h, a\n");
  fprintf(out, "  ld a, l\n");
  fprintf(out, "  %s %02x\n", alu_str[alu_op], value & 0xff);
  fprintf(out, "  ld l, a\n");
  fprintf(out, "  push hl\n");

  return 0;
}
