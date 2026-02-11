operator+ (const Path& lhs_path, const Path& rhs_path)
{
	Path tmp_path(lhs_path);

	tmp_path.m_dirs.insert(tmp_path.m_dirs.end(), rhs_path.m_dirs.begin(), rhs_path.m_dirs.end());
	return tmp_path;
}
