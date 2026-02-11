getValue(const ValueOffset& offset) const
{
	if (offset.first == 0) {
		clever_assert(offset.second < m_data.size(),
				"`offset.second` must be within `m_data` limits.");

		return m_data[offset.second];
	}

	size_t depth = offset.first;
	Environment* env = m_outer;

	while (env && --depth) {
		env = env->m_outer;
	}

	clever_assert(depth == 0,
			"`depth` must be zero, otherwise we failed to find the environment.");
	clever_assert(offset.second < env->m_data.size(),
			"`offset.second` must be within `m_data` bounds.");
	clever_assert_not_null(env);

	return env->m_data[offset.second];
}
