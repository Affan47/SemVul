get_vector (std::vector<guint> &vector,gchar sep,gboolean empty)
{
	if (empty)
		vector.clear ();

	std::string line = value_;
	if (sep != ' ')
		std::replace (line.begin(), line.end(), sep, ' ');

	std::stringstream ss (line);
	guint tmp;
	while (ss >> tmp)
		vector.push_back (tmp);
}
