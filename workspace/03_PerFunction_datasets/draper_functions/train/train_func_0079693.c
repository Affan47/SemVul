wmc(CACHET_OUTPUT& r) const {
	if (size() <= 0) {
		r.prob = 1;
		r.time = 0;
		return;
	}


	FILE *f;
	string wmc_file(gcmd_line.wmc_file);
	if ((f = fopen (wmc_file.c_str(), "r")) == NULL)
	{
		printf("Model counting software not found! File %s, line %d.\n",__FILE__,__LINE__);
		exit(1);
	}
	fclose(f);


	string cnf_file = string(gcmd_line.ops_file_name) + string("__") + string(gcmd_line.fct_file_name) + string(".cnf");
	string result_file = cnf_file + string(".cachet");

	write_cnf_file(cnf_file.c_str());
	string cmd = wmc_file + " " + cnf_file + " > " + result_file;


	system(cmd.c_str());


	read_wmc_answer_file(result_file, r);


	remove(cnf_file.c_str());
	remove(result_file.c_str());
}
