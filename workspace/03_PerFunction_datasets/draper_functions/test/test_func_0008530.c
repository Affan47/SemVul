avr_dup_part(AVRPART * d)
{
  AVRPART * p;
  LISTID save;
  LNODEID ln;
  int i;

  p = avr_new_part();
  save = p->mem;

  *p = *d;

  p->mem = save;

  for (ln=lfirst(d->mem); ln; ln=lnext(ln)) {
    ladd(p->mem, avr_dup_mem(ldata(ln)));
  }

  for (i = 0; i < AVR_OP_MAX; i++) {
    p->op[i] = avr_dup_opcode(p->op[i]);
  }

  return p;
}
