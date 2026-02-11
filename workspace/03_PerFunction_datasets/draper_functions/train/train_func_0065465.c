visit(BasicBlock *bb)
{
   Instruction *next;
   for (Instruction *i = bb->getEntry(); i; i = next) {
      next = i->next;
      switch (i->op) {
      case OP_ABS:
         handleABS(i);
         break;
      case OP_ADD:
         handleADD(i);
         break;
      case OP_RCP:
         handleRCP(i);
         break;
      case OP_MIN:
      case OP_MAX:
         handleMINMAX(i);
         break;
      case OP_SLCT:
         handleSLCT(i);
         break;
      case OP_AND:
      case OP_OR:
      case OP_XOR:
         handleLOGOP(i);
         break;
      case OP_CVT:
         handleCVT(i);
         break;
      case OP_SUCLAMP:
         handleSUCLAMP(i);
         break;
      default:
         break;
      }
   }

   return true;
}
