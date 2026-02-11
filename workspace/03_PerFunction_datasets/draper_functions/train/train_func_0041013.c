create_sap_record(uint8_t channel)
{
	sdp_list_t *apseq, *aproto, *profiles, *proto[2], *root, *svclass_id;
	uuid_t sap_uuid, gt_uuid, root_uuid, l2cap, rfcomm;
	sdp_profile_desc_t profile;
	sdp_record_t *record;
	sdp_data_t *ch;

	record = sdp_record_alloc();
	if (!record)
		return NULL;

	sdp_uuid16_create(&root_uuid, PUBLIC_BROWSE_GROUP);
	root = sdp_list_append(NULL, &root_uuid);
	sdp_set_browse_groups(record, root);
	sdp_list_free(root, NULL);

	sdp_uuid16_create(&sap_uuid, SAP_SVCLASS_ID);
	svclass_id = sdp_list_append(NULL, &sap_uuid);
	sdp_uuid16_create(&gt_uuid, GENERIC_TELEPHONY_SVCLASS_ID);
	svclass_id = sdp_list_append(svclass_id, &gt_uuid);

	sdp_set_service_classes(record, svclass_id);
	sdp_list_free(svclass_id, NULL);

	sdp_uuid16_create(&profile.uuid, SAP_PROFILE_ID);
	profile.version = SAP_VERSION;
	profiles = sdp_list_append(NULL, &profile);
	sdp_set_profile_descs(record, profiles);
	sdp_list_free(profiles, NULL);

	sdp_uuid16_create(&l2cap, L2CAP_UUID);
	proto[0] = sdp_list_append(NULL, &l2cap);
	apseq = sdp_list_append(NULL, proto[0]);

	sdp_uuid16_create(&rfcomm, RFCOMM_UUID);
	proto[1] = sdp_list_append(NULL, &rfcomm);
	ch = sdp_data_alloc(SDP_UINT8, &channel);
	proto[1] = sdp_list_append(proto[1], ch);
	apseq = sdp_list_append(apseq, proto[1]);

	aproto = sdp_list_append(NULL, apseq);
	sdp_set_access_protos(record, aproto);

	sdp_set_info_attr(record, "SIM Access Server", NULL, NULL);

	sdp_data_free(ch);
	sdp_list_free(proto[0], NULL);
	sdp_list_free(proto[1], NULL);
	sdp_list_free(apseq, NULL);
	sdp_list_free(aproto, NULL);

	return record;
}
