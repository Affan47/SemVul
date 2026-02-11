parseHeader() {
	StreamSource& in = source_;
	numVars_ = products_ = soft_ = min_ = max_ = 0;
	int64 sum= 0;
	delete nlc_; nlc_ = 0;
	const int MAX     = INT_MAX;
	if (!match(in, "* #variable=", false)){ ERROR("Missing problem line \"* #variable=\""); }
	in.skipWhite();
	if (!in.parseInt(numVars_,0,varMax))  { ERROR("Number of vars expected\n"); }
	if (!match(in, "#constraint=", true)) { ERROR("Bad problem line. Missing \"#constraint=\""); }
	int numCons;
	if (!in.parseInt(numCons, 0, MAX))    { ERROR("Number of constraints expected\n"); }
	if (match(in, "#", true)) {
		const char* next = "soft=";
		if (match(in, "product=", true))    {
			if (!in.parseInt(products_,0,MAX)){ ERROR("Number of products expected\n"); }
			next = "sizeproduct=";
			if (!match(in, next,true))        { ERROR("'sizeproduct=' expected\n"); }
			int prodLits = 0;
			if (!in.parseInt(prodLits,0,MAX)) { ERROR("Number of product literals expected\n"); }
			nlc_ = new NLCData(prodLits+products_);
			next = "#soft=";
		}
		if (match(in, next, true))          {
			if (!in.parseInt(soft_,0,MAX))    { ERROR("Number of soft constraints expected\n"); }
			if (!match(in, "mincost=", true)) { ERROR("'mincost=' expected\n"); }
			if (!in.parseInt(min_))           { ERROR("Minimal cost expected\n"); }
			if (!match(in, "maxcost=", true)) { ERROR("'maxcost=' expected\n"); }
			if (!in.parseInt(max_))           { ERROR("Maximal cost expected\n"); }
			if (!match(in, "sumcost=", true)) { ERROR("'sumcost=' expected\n"); }
			if (!in.parseInt64(sum))          { ERROR("Sum of soft constraints cost expected\n"); }
		}
	}
	if (!matchEol(in, true))              { ERROR("Unrecognized characters in problem line\n"); }


	maxVar_  = numVars_ + soft_ + products_;
	nextVar_ = numVars_;
	ctx_.reserveVars(maxVar_+1);
	ctx_.symTab().startInit();
	for (int v = 1; v <= maxVar_; ++v) {
		ctx_.addVar(Var_t::atom_var);
	}
	ctx_.symTab().endInit(SymbolTable::map_direct, numVars_+1);
	ctx_.startAddConstraints();
}
