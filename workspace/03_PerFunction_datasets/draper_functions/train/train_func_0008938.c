recv_vec4(vvp_net_ptr_t ptr, const vvp_vector4_t&bit,
                           vvp_context_t)
{
      dispatch_operand_(ptr, bit);

      vvp_vector4_t out (op_a_.size());

      unsigned long shift;
      if (! vector4_to_value(op_b_, shift)) {
	    vvp_send_vec4(ptr.ptr()->out, x_val_, 0);
	    return;
      }

      if (shift > out.size())
	    shift = out.size();

      for (unsigned idx = shift ;  idx < out.size() ;  idx += 1)
	    out.set_bit(idx-shift, op_a_.value(idx));

      vvp_bit4_t pad = BIT4_0;
      if (signed_flag_ && op_a_.size() > 0)
	    pad = op_a_.value(op_a_.size()-1);

      for (unsigned idx = 0 ;  idx < shift ;  idx += 1)
	    out.set_bit(idx+out.size()-shift, pad);

      vvp_send_vec4(ptr.ptr()->out, out, 0);
}
