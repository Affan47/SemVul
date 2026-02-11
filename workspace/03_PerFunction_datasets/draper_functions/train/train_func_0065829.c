wide_inputs_connect(vvp_wide_fun_core*core,
			 unsigned argc, struct symb_s*argv)
{


      unsigned input_functors = (argc+3) / 4;
      for (unsigned idx = 0 ;  idx < input_functors ;  idx += 1) {
	    unsigned base = idx*4;
	    unsigned trans = 4;
	    if (base+trans > argc)
		  trans = argc - base;

	    vvp_wide_fun_t*cur = new vvp_wide_fun_t(core, base);
	    vvp_net_t*ptr = new vvp_net_t;
	    ptr->fun = cur;

	    inputs_connect(ptr, trans, argv+base);
      }
}
