report(const Json &result) {
	if (!quiet) {
	    lcdf::StringAccum sa;
	    double dv;
	    if (result.count("puts"))
		sa << " total " << result.get("puts");
	    if (result.get("puts_per_sec", dv))
		sa.snprintf(100, " %.0f put/s", dv);
	    if (result.get("gets_per_sec", dv))
		sa.snprintf(100, " %.0f get/s", dv);
	    if (!sa.empty())
		notice(sa.take_string());
	}
	printf("%s\n", result.unparse().c_str());
    }
