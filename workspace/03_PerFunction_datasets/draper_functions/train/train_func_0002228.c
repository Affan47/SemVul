handleCALL(Instruction *i)
{
   if (prog->getType() == Program::TYPE_COMPUTE) {

      i->setSrc(i->srcCount(), tid);
   }
   return true;
}
