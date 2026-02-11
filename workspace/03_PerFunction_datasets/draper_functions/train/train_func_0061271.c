return_local(int index, int local_count)
{
  fprintf(out, "; return_local\n");
  fprintf(out, "  ldy locals\n");
  fprintf(out, "  lda stack_lo - %d,y\n", LOCALS(index));
  fprintf(out, "  sta result + 0\n");
  fprintf(out, "  lda stack_hi - %d,y\n", LOCALS(index));
  fprintf(out, "  sta result + 1\n");

  fprintf(out, "  ldx locals\n");

  if (!is_main)
  {
    POP_HI;
    POP_LO;
    fprintf(out, "  sta locals\n");
  }

  fprintf(out, "  rts\n");

  return 0;
}
