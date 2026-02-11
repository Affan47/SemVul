result_item_level_policy_changed(result_item_t * item, apol_policy_t * orig_pol, apol_policy_t * mod_pol)
{
	qpol_policy_t *oq = apol_policy_get_qpol(orig_pol);
	qpol_policy_t *mq = apol_policy_get_qpol(mod_pol);
	if (!qpol_policy_has_capability(oq, QPOL_CAP_MLS) && !qpol_policy_has_capability(mq, QPOL_CAP_MLS)) {
		item->supported = 0;
	} else {
		item->supported = 1;
	}
}
