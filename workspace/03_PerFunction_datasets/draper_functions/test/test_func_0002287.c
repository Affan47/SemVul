disassemble(Expression *expr)
{
  Processor *cpu = GetActiveCPU();
  if(cpu) {


    int start = -10;
    int end = 5;

    if(expr) {

      try {
        Value *v = expr->evaluate();

        AbstractRange *ar = dynamic_cast<AbstractRange *>(v);
        if(ar) {
          start = ar->get_leftVal();
          end = ar->get_rightVal();
        } else if (v) {
          start = 0;
          gint64 i;
          v->get(i);
          end = (int) i;
        }
      }

      catch (Error *err) {
        if(err)
          cout << "ERROR:" << err->toString() << endl;
        delete err;
      }

    }

    if(cpu->pma) {
      int current_pc = cpu->pma->get_PC();

      if(start<0) {
	start += current_pc;
	end   += current_pc;
      }

      cout << hex << " current pc = 0x"<<current_pc << endl;
      cpu->disassemble(start, end);
    }

  }

}
