match_headers(struct mem_obj *obj, struct request *rq, int *flags)
{
struct	header_action	*curr = actions;
char			*old_value = NULL, *req_value = NULL;
int			matched = TRUE, agents_equal;

    RDLOCK_VARY_CONFIG ;

    while ( curr ) {

	if ( curr->action == ACTION_IGNORE ) {
	    curr = curr->next;
	    continue;
	}


	old_value = fetch_internal_rq_header(obj, curr->header);
	req_value = attr_value(rq->av_pairs, curr->header);
	if ( !req_value && old_value)  {
	    matched = FALSE;
	    break;
	}
	if ( !old_value ) {
	    curr = curr->next;
	    continue;
	}
	switch ( curr->action ) {
	case(ACTION_BYCHARSET):
		agents_equal = Compare_Agents(old_value, req_value);
		if ( !agents_equal ) {
		    matched = FALSE;
		    break;
		}
		break;
	default:
		break;
	}
	curr = curr->next;
    }

    UNLOCK_VARY_CONFIG ;
    if ( matched )
	return(MOD_CODE_OK);
    return(MOD_CODE_ERR);
}
