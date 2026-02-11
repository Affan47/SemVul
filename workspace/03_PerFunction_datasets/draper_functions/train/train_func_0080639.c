emitTEXBAR(const Instruction *i)
{
   code[0] = 0x00000006 | (i->subOp << 26);
   code[1] = 0xf0000000;
   emitPredicate(i);
   emitCondCode(i->flagsSrc >= 0 ? i->cc : CC_ALWAYS, 5);
}
