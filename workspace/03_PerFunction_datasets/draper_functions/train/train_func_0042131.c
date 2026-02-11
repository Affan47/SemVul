readPts(
	ANNpointArray		&pa,
	int					&n,
	char				*file_nm,
	PtType				type)
{
	int i;


	ifstream in_file(file_nm);
	if (!in_file) {
		cerr << "File name: " << file_nm << "\n";
		Error("Cannot open input data/query file", ANNabort);
	}

	if (pa != NULL) annDeallocPts(pa);
	pa = annAllocPts(n, dim);

	for (i = 0; i < n; i++) {
		if (!(in_file >> pa[i][0])) break;
		for (int d = 1; d < dim; d++) {
			in_file >> pa[i][d];
		}
	}

	char ignore_me;
	in_file >> ignore_me;
	if (!in_file.eof()) {
		if (type == DATA)
			Error("`data_size' too small. Input file truncated.", ANNwarn);
		else
			Error("`query_size' too small. Input file truncated.", ANNwarn);
	}
	n = i;


	if (stats > SILENT) {
		if (type == DATA) {
			cout << "[Read Data Points:\n";
			cout << "  data_size  = " << n << "\n";
		}
		else {
			cout << "[Read Query Points:\n";
			cout << "  query_size = " << n << "\n";
		}
		cout << "  file_name  = " << file_nm << "\n";
		cout << "  dim        = " << dim << "\n";

		if ((type == DATA && stats >= SHOW_PTS) ||
			(type == QUERY && stats >= QUERY_RES)) {
			cout << "  (Points:\n";
			for (i = 0; i < n; i++) {
				cout << "    " << i << "\t";
				printPoint(pa[i], dim);
				cout << "\n";
			}
			cout << "  )\n";
		}
		cout << "]\n";
	}
}
