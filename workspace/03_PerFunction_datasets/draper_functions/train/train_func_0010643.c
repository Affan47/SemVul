gkm_mock_C_GetSlotList (CK_BBOOL tokenPresent, CK_SLOT_ID_PTR pSlotList, CK_ULONG_PTR pulCount)
{
	CK_ULONG count;

	g_assert (pulCount != NULL && "Invalid pulCount");

	count = tokenPresent ? 1 : 2;


	if (pSlotList == NULL) {
		*pulCount = count;
		return CKR_OK;
	}

	if (*pulCount < count) {
		g_assert (*pulCount && "Passed in a bad count");
		return CKR_BUFFER_TOO_SMALL;
	}

	*pulCount = count;
	pSlotList[0] = GKM_TEST_SLOT_ONE;
	if (!tokenPresent)
		pSlotList[1] = GKM_TEST_SLOT_TWO;

	return CKR_OK;
}
