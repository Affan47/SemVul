get_ts_const(const char*&cp, int&res, bool is_units)
{

      if (*cp != '1') {
	    if (is_units) {
		  cerr << "Error: Invalid +timescale units constant "
		          "(1st digit)." << endl;
	    } else {
		  cerr << "Error: Invalid +timescale precision constant "
		          "(1st digit)." << endl;
	    }
	    return true;
      }
      cp += 1;


      res = strspn(cp, "0");
      if (res > 2) {
	    if (is_units) {
		  cerr << "Error: Invalid +timescale units constant "
		          "(number of zeros)." << endl;
	    } else {
		  cerr << "Error: Invalid +timescale precision constant "
		          "(number of zeros)." << endl;
	    }
	    return true;
      }
      cp += res;


      if (strncmp("s", cp, 1) == 0) {
	    res -= 0;
	    cp += 1;
	    return false;

      } else if (strncmp("ms", cp, 2) == 0) {
	    res -= 3;
	    cp += 2;
	    return false;

      } else if (strncmp("us", cp, 2) == 0) {
	    res -= 6;
	    cp += 2;
	    return false;

      } else if (strncmp("ns", cp, 2) == 0) {
	    res -= 9;
	    cp += 2;
	    return false;

      } else if (strncmp("ps", cp, 2) == 0) {
	    res -= 12;
	    cp += 2;
	    return false;

      } else if (strncmp("fs", cp, 2) == 0) {
	    res -= 15;
	    cp += 2;
	    return false;

      }

      if (is_units) {
	    cerr << "Error: Invalid +timescale units scale." << endl;
      } else {
	    cerr << "Error: Invalid +timescale precision scale." << endl;
      }
      return true;
}
