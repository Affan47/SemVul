set_param (int id, wxString param)
{
	if (type == concat) {
		concats.push_back (param);
		return;
	} else if (type == replace) {
		if (id == 0)
			base = param;
		else if (id == 1)
			substr = param;
		else if (id == 2)
			substr_new = param;
		else
			std::cerr << "Bad id for replace in set_param().\n";
		return;
	}

	std::cerr << "Bad set_param() call.\n";
}
