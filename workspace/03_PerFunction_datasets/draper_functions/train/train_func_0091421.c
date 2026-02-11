run_procedure (string pname)
{
  for (uint i = 0; i < gf.size ("procedure"); i ++)
    if (ci_equal (gf.block ("procedure", i).name, pname))
      {
	const GeasBlock &proc = gf.block ("procedure", i);

	for (uint j = 0; j < proc.data.size(); j ++)
	  {

	    run_script(proc.data[j]);
	  }
	return;
      }
  gi->debug_print ("No procedure " + pname + " found.");
}
