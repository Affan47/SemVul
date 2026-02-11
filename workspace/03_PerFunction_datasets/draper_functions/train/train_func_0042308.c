query_answer_partials_changed(property_t prop)
{
	(void) prop;

	if (GNET_PROPERTY(pfsp_server)) {
		share_update_matching_information();
	} else {


		g_assert(!share_can_answer_partials());
	}
	return FALSE;
}
