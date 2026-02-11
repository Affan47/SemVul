set_svar (string varname, uint index, string varval)
{
  uint n, m;
  if (!find_svar (varname, n))
    {
      if (find_ivar (varname, m))
	{
	  gi->debug_print ("Defining " + varname + " as string variable when there is already a numeric variable of that name.");
	  return;
	}
      SVarRecord svr;
      svr.name = varname;
      n = state.svars.size();
      state.svars.push_back (svr);
    }
  state.svars[n].set(index, varval);
  if (index == 0)
    {
      for (uint varn = 0; varn < gf.size("variable"); varn ++)
	{
	  const GeasBlock &go (gf.block ("variable", varn));
	  if (ci_equal (go.name, varname))
	    {
	      string script = "";
	      uint c1, c2;
	      for (uint j = 0; j < go.data.size(); j ++)

		if (first_token (go.data[j], c1, c2) == "onchange")
		  script = trim (go.data[j].substr (c2 + 1));
	      if (script != "")
		run_script (script);
	    }
	}
    }
}
