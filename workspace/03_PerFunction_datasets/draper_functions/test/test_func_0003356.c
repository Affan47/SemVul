emitVectorSubOp(const Instruction *i)
{
   switch (NV50_IR_SUBOP_Vn(i->subOp)) {
   case 0:
      code[1] |= (i->subOp & 0x000f) << 12;
      code[1] |= (i->subOp & 0x00e0) >> 5;
      code[1] |= (i->subOp & 0x0100) << 7;
      code[1] |= (i->subOp & 0x3c00) << 13;
      break;
   case 1:
      code[1] |= (i->subOp & 0x000f) << 8;
      code[1] |= (i->subOp & 0x0010) << 11;
      code[1] |= (i->subOp & 0x01e0) >> 1;
      code[1] |= (i->subOp & 0x0200) << 6;
      code[1] |= (i->subOp & 0x3c00) << 2;
      code[1] |= (i->mask & 0x3) << 2;
      break;
   case 2:
      code[1] |= (i->subOp & 0x000f) << 8;
      code[1] |= (i->subOp & 0x01e0) >> 1;
      code[1] |= (i->subOp & 0x3c00) << 2;
      code[1] |= (i->mask & 0x3) << 2;
      code[1] |= (i->mask & 0xc) << 21;
      break;
   default:
      assert(0);
      break;
   }
}
