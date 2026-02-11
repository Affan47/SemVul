loadData(UINT64 *offset, TCSD_PACKET_TYPE data_type, void *data, int data_size, BYTE *blob)
{
	switch (data_type) {
		case TCSD_PACKET_TYPE_BYTE:
			Trspi_LoadBlob_BYTE(offset, *((BYTE *) (data)), blob);
			break;
		case TCSD_PACKET_TYPE_BOOL:
			Trspi_LoadBlob_BOOL(offset, *((TSS_BOOL *) (data)), blob);
			break;
		case TCSD_PACKET_TYPE_UINT16:
			Trspi_LoadBlob_UINT16(offset, *((UINT16 *) (data)), blob);
			break;
		case TCSD_PACKET_TYPE_UINT32:
			Trspi_LoadBlob_UINT32(offset, *((UINT32 *) (data)), blob);
			break;
		case TCSD_PACKET_TYPE_PBYTE:
			Trspi_LoadBlob(offset, data_size, blob, (BYTE *)data);
			break;
		case TCSD_PACKET_TYPE_NONCE:
			Trspi_LoadBlob(offset, 20, blob, ((TCPA_NONCE *)data)->nonce);
			break;
		case TCSD_PACKET_TYPE_DIGEST:
			Trspi_LoadBlob(offset, 20, blob, ((TCPA_DIGEST *)data)->digest);
			break;
		case TCSD_PACKET_TYPE_AUTH:
			LoadBlob_AUTH(offset, blob, ((TPM_AUTH *)data));
			break;
		case TCSD_PACKET_TYPE_UUID:
			Trspi_LoadBlob_UUID(offset, blob, *((TSS_UUID *)data));
			break;
		case TCSD_PACKET_TYPE_ENCAUTH:
			Trspi_LoadBlob(offset, 20, blob, ((TCPA_ENCAUTH *)data)->authdata);
			break;
		case TCSD_PACKET_TYPE_VERSION:
			Trspi_LoadBlob_TCPA_VERSION(offset, blob, *((TCPA_VERSION *)data));
			break;
#ifdef TSS_BUILD_PS
		case TCSD_PACKET_TYPE_LOADKEY_INFO:
			LoadBlob_LOADKEY_INFO(offset, blob, ((TCS_LOADKEY_INFO *)data));
			break;
#endif
		case TCSD_PACKET_TYPE_PCR_EVENT:
			Trspi_LoadBlob_PCR_EVENT(offset, blob, ((TSS_PCR_EVENT *)data));
			break;
		case TCSD_PACKET_TYPE_COUNTER_VALUE:
			Trspi_LoadBlob_COUNTER_VALUE(offset, blob, ((TPM_COUNTER_VALUE *)data));
			break;
		case TCSD_PACKET_TYPE_SECRET:
			Trspi_LoadBlob(offset, 20, blob, ((TCPA_SECRET *)data)->authdata);
			break;
		default:
			LogError("TCSD packet type unknown! (0x%x)", data_type & 0xff);
			return TSPERR(TSS_E_INTERNAL_ERROR);
	}

	return TSS_SUCCESS;
}
