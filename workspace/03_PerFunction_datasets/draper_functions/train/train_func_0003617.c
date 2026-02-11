visit(class ir_return * ir)
   {


      truncate_after_instruction(ir);


      this->block.min_strength = strength_return;


   }
