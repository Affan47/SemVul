stack_alu(int alu_op)
{
  fprintf(out, "  ;; stack_alu(%s)\n", alu_str[alu_op]);
  if (alu_op <= ALU_SUB)
  {
#if 0
    fprintf(out, "  pop bc\n");
    fprintf(out, "  pop hl\n");


    fprintf(out, "  and a   ; clear carry\n");
    fprintf(out, "  %s hl, bc\n", alu_str[alu_op]);
    fprintf(out, "  push hl\n");
#endif

    fprintf(out, "  pop hl\n");
    fprintf(out, "  pop bc\n");
    if (alu_op == ALU_SUB)
    {
      fprintf(out, "  and a   ; clear carry\n");
    }
    fprintf(out, "  %s hl, bc\n", alu_str[alu_op]);
    fprintf(out, "  push hl\n");
    stack--;
  }
    else
  {

    fprintf(out, "  pop hl\n");
    fprintf(out, "  pop bc\n");
    fprintf(out, "  ld a, b\n");
    fprintf(out, "  %s a, h\n", alu_str[alu_op]);
    fprintf(out, "  ld h, a\n");
    fprintf(out, "  ld a, c\n");
    fprintf(out, "  %s a, l\n", alu_str[alu_op]);
    fprintf(out, "  ld l, a\n");
    fprintf(out, "  push hl\n");
  }

  return 0;
}
