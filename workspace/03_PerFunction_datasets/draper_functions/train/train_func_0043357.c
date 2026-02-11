recv_real(vvp_net_ptr_t ptr, double bit,
                                   vvp_context_t)
{
      dispatch_operand_(ptr, bit);

      double val = op_a_ / op_b_;
      vvp_send_real(ptr.ptr()->out, val, 0);
}
