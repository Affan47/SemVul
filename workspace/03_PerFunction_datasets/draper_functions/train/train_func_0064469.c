SimpleFromAddress() const
{
	if( From.size() ) {

		std::string ret;
		for( size_t i = 0; i < From[0].Email.size(); i++ )
			if( From[0].Email[i] != ' ' )
				ret += From[0].Email[i];

		return ret;
	}
	else {
		return _("unknown");
	}
}
