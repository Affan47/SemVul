create_rule()
{
	struct rule	*result;

	if ( (result=(struct rule *)malloc(sizeof(struct rule))) == NULL )
		return NULL;

	result->match_regex=NULL;
	result->match_regex_str=NULL;
	result->match_not_regex=NULL;
	result->match_not_regex_str=NULL;
	result->stop_regex=NULL;
	result->stop_regex_str=NULL;
	result->stop_not_regex=NULL;
	result->stop_not_regex_str=NULL;
	result->timeout=LONG_MAX;
	result->do_continue=0;
	result->action_type=ACTION_UNKNOWN;
	result->action_body=NULL;
	result->next=NULL;
	result->previous=NULL;

	return(result);
}
