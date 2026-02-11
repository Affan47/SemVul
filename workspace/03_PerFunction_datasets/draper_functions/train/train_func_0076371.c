recv_vec4(vvp_net_ptr_t ptr, const vvp_vector4_t&bit,
                              vvp_context_t)
{
      dispatch_operand_(ptr, bit);

      vvp_net_t*net = ptr.ptr();

      vvp_vector4_t value (wid_);


      const vvp_bit4_t pad = BIT4_1;

      vvp_bit4_t carry = BIT4_1;
      for (unsigned idx = 0 ;  idx < wid_ ;  idx += 1) {
	    vvp_bit4_t a = (idx >= op_a_.size())? pad : op_a_.value(idx);
	    vvp_bit4_t b = (idx >= op_b_.size())? pad : ~op_b_.value(idx);
	    vvp_bit4_t cur = add_with_carry(a, b, carry);

	    if (cur == BIT4_X) {
		  vvp_send_vec4(net->out, x_val_, 0);
		  return;
	    }

	    value.set_bit(idx, cur);
      }

      vvp_send_vec4(net->out, value, 0);
}
