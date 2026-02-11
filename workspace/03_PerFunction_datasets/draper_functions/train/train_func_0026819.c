warn_param_ob(long par_msv, long par_lsv, bool defined,
                          long par_base, unsigned long wid, long pwid,
                          const LineInfo *info, perm_string name, bool up)
{
      long par_max;

      if (defined) {
	    if (par_msv < par_lsv) par_max = par_lsv-par_msv;
	     else par_max = par_msv-par_lsv;
      } else {
	    if (pwid < 0) par_max = integer_width;
	    else par_max = pwid;
      }


      if (par_base < 0) {
	    cerr << info->get_fileline() << ": warning: " << name << "["
	         << par_base;
	    if (up) cerr << "+:";
	    else cerr << "-:";
	    cerr << wid << "] is selecting before vector." << endl;
      }


      if (par_base + (long)wid - 1 > par_max) {
	    cerr << info->get_fileline() << ": warning: " << name << "["
	         << par_base << "+:" << wid << "] is selecting after vector."
	         << endl;
      }
}
