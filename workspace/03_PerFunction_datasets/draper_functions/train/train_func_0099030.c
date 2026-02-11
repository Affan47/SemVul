decode_base(uint8_t type, uint16_t *loc)
{
  if     (type == 0) *loc = WORD(pc++);
  else if(type == 1) *loc = BYTE(pc);
  else if(type == 2) *loc = variable(BYTE(pc));
  else               return 0;

  pc++;

  return 1;
}
