getState (const std::vector<unsigned long> & v) {
  if (v.size() != VECTOR_STATE_SIZE ) {
    std::cerr <<
    	"\nRanluxEngine get:state vector has wrong length - state unchanged\n";
    return false;
  }
  for (int i=0; i<24; ++i) {
    float_seed_table[i] = v[i+1]*mantissa_bit_24();
	#ifdef TRACE_IO
	std::cout <<
	"float_seed_table[" << i << "] = " << float_seed_table[i] << "\n";
	#endif
  }
  i_lag    = v[25];
  j_lag    = v[26];
  carry    = v[27]*mantissa_bit_24();
  count24  = v[28];
  luxury   = v[29];
  nskip    = v[30];
	#ifdef TRACE_IO
	std::cout << "i_lag: " << i_lag << "  j_lag: " << j_lag
		  << "  carry: " << carry << "\n";
	std::cout << "count24: " << count24 << "  luxury: " << luxury
		  << "  nskip: " << nskip << "\n";

	#endif
	#ifdef TRACE_IO
	flat_trace = true;
	#endif
  return true;
}
