show_lpm_cast_int(ivl_lpm_t net)
{
      unsigned width = ivl_lpm_width(net);
      ivl_nexus_t q, a;

      fprintf(out, "  LPM_CAST_INT %s: <width=%u>\n",
	      ivl_lpm_basename(net), width);

      q = ivl_lpm_q(net,0);
      a = ivl_lpm_data(net,0);
      fprintf(out, "    O: %p\n", ivl_lpm_q(net,0));
      fprintf(out, "    A: %p\n", ivl_lpm_data(net,0));

      if (type_of_nexus(q) == IVL_VT_REAL) {
	    fprintf(out, "    ERROR: Data type of Q is %s, expecting !real\n",
		    data_type_string(type_of_nexus(q)));
	    stub_errors += 1;
      }

      if (type_of_nexus(a) != IVL_VT_REAL) {
	    fprintf(out, "    ERROR: Data type of A is %s, expecting real\n",
		    data_type_string(type_of_nexus(a)));
	    stub_errors += 1;
      }
}
