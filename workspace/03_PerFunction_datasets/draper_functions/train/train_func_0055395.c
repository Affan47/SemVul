do_setrelpath(char** argv) {
	string bin    = argv[0];
	string lib    = argv[1];
	string data   = argv[2];
	string doc    = argv[3];
	string config = argv[4];
	cout << "GLE will be installed as follows:" << endl;
	cout << "Binary:   \"" << bin << "\"" << endl;
	cout << "Library:  \"" << lib << "\"" << endl;

	string rel_lib;
	int rel_lib_nb;
	GLEFindRelPath(bin, lib, &rel_lib, &rel_lib_nb);
	cout << "          (Up: " << rel_lib_nb << ", Relative: \"" << rel_lib << "\")" << endl;

	string rel_data;
	int rel_data_nb;
	GLEFindRelPath(bin, data, &rel_data, &rel_data_nb);
	cout << "GLE_TOP:  \"" << data << "\"" << endl;
	cout << "          (Up: " << rel_data_nb << ", Relative: \"" << rel_data << "\")" << endl;

	string rel_doc;
	int rel_doc_nb;
	GLEFindRelPath(data, doc, &rel_doc, &rel_doc_nb);
	cout << "DOC:      \"" << doc << "\"" << endl;
	cout << "          (Up: " << rel_doc_nb << ", Relative: \"" << rel_doc << "\")" << endl;

	vector<string> lines;
	ifstream ifile(config.c_str());
	if (!ifile.good()) {
		cout << "Can't open: '" << config << "'" << endl;
		return -1;
	}
	while (!ifile.eof()) {
		string line;
		ReadFileLine(ifile, line);
		if (str_i_str(line.c_str(), "[SETRELPATH]")) {
			break;
		}
		lines.push_back(line);
	}
	ifile.close();
	ofstream ofile(config.c_str());
	for (vector<string>::size_type i = 0; i < lines.size(); i++) {
		ofile << lines[i] << endl;
	}
	ofile << endl;
	ofile << "/* [SETRELPATH]: The following lines have been added by 'build/bin/setrelpath' */" << endl;
	ofile << "#define GLETOP_CD " << rel_data_nb << endl;
	ofile << "#define GLETOP_REL \"" << rel_data << "\"" << endl;
	ofile << "#define GLETOP_ABS \"" << data << "\"" << endl;
	ofile << endl;
	ofile << "#define GLELIB_CD " << rel_lib_nb << endl;
	ofile << "#define GLELIB_REL \"" << rel_lib << "\"" << endl;
	ofile << "#define GLELIB_ABS \"" << lib << "\"" << endl;
	ofile << endl;
	ofile << "#define GLEDOC_CD " << rel_doc_nb << endl;
	ofile << "#define GLEDOC_REL \"" << rel_doc << "\"" << endl;
	ofile << "#define GLEDOC_ABS \"" << doc << "\"" << endl;
	ofile << endl;
	ofile.close();
	return 0;
}
