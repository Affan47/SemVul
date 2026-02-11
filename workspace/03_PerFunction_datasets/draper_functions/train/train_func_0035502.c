pop_callstub(glui32 returnvalue)
{
  glui32 desttype, destaddr;
  glui32 newpc, newframeptr;

  if (stackptr < 16)
    fatal_error("Stack underflow in callstub.");
  stackptr -= 16;

  newframeptr = Stk4(stackptr+12);
  newpc = Stk4(stackptr+8);
  destaddr = Stk4(stackptr+4);
  desttype = Stk4(stackptr+0);

  pc = newpc;
  frameptr = newframeptr;


  valstackbase = frameptr + Stk4(frameptr);
  localsbase = frameptr + Stk4(frameptr+4);

  switch (desttype) {

  case 0x11:
    fatal_error("String-terminator call stub at end of function call.");
    break;

  case 0x10:


    stream_string(pc, 0xE1, destaddr);
    break;

  case 0x12:


    stream_num(pc, TRUE, destaddr);
    break;

  case 0x13:


    stream_string(pc, 0xE0, destaddr);
    break;

  case 0x14:


    stream_string(pc, 0xE2, destaddr);
    break;

  default:


    store_operand(desttype, destaddr, returnvalue);
    break;
  }
}
