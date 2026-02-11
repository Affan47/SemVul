g_check_bounds(const char* after) {
	if (g.xmin == -1e30 || g.xmax == 1e30 || g.ymin == -1e30 || g.ymax == 1e30) {
		ostringstream ostr;
		ostr << "bounds error: " << after << endl;
		ostr << "yields : " << g.xmin << ", " << g.ymin << endl;
		ostr << "yields : " << g.xmax << ", " << g.ymax;
		g_throw_parser_error(ostr.str().c_str());
	}
}
