ppc32_memop_fast_lbz(jit_op_t *iop,int target)
{
   amd64_clear_reg(iop->ob_ptr,AMD64_RCX);
   amd64_mov_reg_memindex(iop->ob_ptr,AMD64_RCX,AMD64_RBX,0,AMD64_RSI,0,1);
   ppc32_store_gpr(&iop->ob_ptr,target,AMD64_RCX);
}
