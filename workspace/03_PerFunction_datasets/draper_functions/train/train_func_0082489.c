print_types()
{
	char **	typelist;

	typelist = stonith_types();
	if (typelist == NULL) {
		log_msg(LOG_ERR, "Could not list Stonith types.");
	}else{
		char **	this;

		for(this=typelist; *this; ++this) {
			printf("%s\n", *this);
		}
	}
}
