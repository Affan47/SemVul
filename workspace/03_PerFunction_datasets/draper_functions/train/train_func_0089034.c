lyxMarkChange(ostream & os, BufferParams const & bparams, int & column,
			    Change const & old, Change const & change)
{
	if (old == change)
		return;

	column = 0;

	int const buffer_id = bparams.authors().get(change.author).bufferId();

	switch (change.type) {
		case Change::UNCHANGED:
			os << "\n\\change_unchanged\n";
			break;

		case Change::DELETED:
			os << "\n\\change_deleted " << buffer_id
				<< " " << change.changetime << "\n";
			break;

		case Change::INSERTED:
			os << "\n\\change_inserted " << buffer_id
				<< " " << change.changetime << "\n";
			break;
	}
}
