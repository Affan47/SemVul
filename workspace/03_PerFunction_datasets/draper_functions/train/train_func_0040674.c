coda(vector<pair<string, Range> > const &nodes,
		   string const &prefix)
{
    if (!_model) {
	_err << "Can't dump CODA output. No model!" << endl;
	return false;
    }


    try {
        string warn;
	_model->coda(nodes, prefix, warn);
        if (!warn.empty()) {
            _err << "WARNINGS:\n" << warn;
        }
    }
    CATCH_ERRORS

    return true;
}
