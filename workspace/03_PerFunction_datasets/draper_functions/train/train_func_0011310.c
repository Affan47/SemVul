AddOptToOpts(string opt, string val, vector<opt_pair> *in_vec) {
	opt_pair optp;

	optp.opt = StrLower(opt);
	optp.val = val;

	in_vec->push_back(optp);
}
