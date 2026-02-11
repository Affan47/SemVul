dispatch_operand_(vvp_net_ptr_t ptr, double bit)
{
      switch (ptr.port()) {
	  case 0:
	    op_a_ = bit;
	    break;
	  case 1:
	    op_b_ = bit;
	    break;
	  default:
	    fprintf(stderr, "Unsupported port type %d.\n", ptr.port());
	    assert(0);
      }
}
