isScoreboardReset(const serverinfo & sinfo) const
{
	if (last_good_serverinfo == NULL) {
		return false;
	}

	serverinfo::players_t::const_iterator pl_it;
	for (pl_it = sinfo.players.begin(); pl_it != sinfo.players.end(); pl_it++) {
		if (pl_it->frags != 0) {
			return false;
		}
	}

	return true;
}
