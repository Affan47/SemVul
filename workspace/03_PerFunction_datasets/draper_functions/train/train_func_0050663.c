gck_mock_C_CloseAllSessions (CK_SLOT_ID slotID)
{
	g_return_val_if_fail (slotID == GCK_MOCK_SLOT_ONE_ID, CKR_SLOT_ID_INVALID);

	g_hash_table_remove_all (the_sessions);
	return CKR_OK;
}
