recv_vec8(vvp_net_ptr_t ptr, const vvp_vector8_t&bit)
{
      if (ptr.port() == 1) {
	    recv_vec4(ptr, reduce4(bit), 0);
	    return;
      }

      if (ptr.port() != 0)
	    return;

      bit_ = bit;
      generate_output_(ptr);
}
