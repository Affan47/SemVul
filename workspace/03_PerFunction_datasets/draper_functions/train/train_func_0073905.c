x86_fn_arg( struct x86_function *p,
                           unsigned arg )
{
   switch(x86_target(p))
   {
   case X86_64_WIN64_ABI:

      switch(arg)
      {
      case 1:
         return x86_make_reg(file_REG32, reg_CX);
      case 2:
         return x86_make_reg(file_REG32, reg_DX);
      case 3:
         return x86_make_reg(file_REG32, reg_R8);
      case 4:
         return x86_make_reg(file_REG32, reg_R9);
      default:

         return x86_make_disp(x86_make_reg(file_REG32, reg_SP),
               p->stack_offset + arg * 8);
      }
   case X86_64_STD_ABI:
      switch(arg)
      {
      case 1:
         return x86_make_reg(file_REG32, reg_DI);
      case 2:
         return x86_make_reg(file_REG32, reg_SI);
      case 3:
         return x86_make_reg(file_REG32, reg_DX);
      case 4:
         return x86_make_reg(file_REG32, reg_CX);
      case 5:
         return x86_make_reg(file_REG32, reg_R8);
      case 6:
         return x86_make_reg(file_REG32, reg_R9);
      default:
         return x86_make_disp(x86_make_reg(file_REG32, reg_SP),
               p->stack_offset + (arg - 6) * 8);
      }
   case X86_32:
      return x86_make_disp(x86_make_reg(file_REG32, reg_SP),
			p->stack_offset + arg * 4);
   default:
      assert(0 && "Unexpected x86 target ABI in x86_fn_arg");
      return x86_make_reg(file_REG32, reg_CX);
   }
}
