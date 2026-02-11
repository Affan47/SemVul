parseBounds(avm::vector<pair<framepos_t, framepos_t> >& boundaries, avm::vector<avm::string>& bound_args)
{
    for(unsigned i = 0; i < bound_args.size(); i++){
	avm::string str = bound_args[i];
	avm::string::size_type pos = str.find(',');
	if (pos != avm::string::npos)
	{
	    pair<framepos_t, framepos_t> pr;
	    pr.first = atoi(str.substr(0, pos).c_str());
	    pr.second = atoi(str.substr(pos+1).c_str());

	    if(pr.second > pr.first){
		boundaries.push_back(pr);
	    }else{
		fprintf(stderr, "second value must be greater than first: %s\n", str.c_str());
	    }
	}else{
	    fprintf(stderr, "need a comma between bounds: %s\n", str.c_str());
	}
    }
}
