HpmfwupgUpgradeStage(struct ipmi_intf *intf,
		struct HpmfwupgUpgradeCtx *pFwupgCtx, int option)
{
	struct HpmfwupgImageHeader *pImageHeader = (struct HpmfwupgImageHeader*)
		pFwupgCtx->pImageData;
	struct HpmfwupgActionRecord* pActionRecord;
	int rc = HPMFWUPG_SUCCESS;
	unsigned char *pImagePtr;
	unsigned int actionsSize;
	int flagColdReset = FALSE;
	time_t start,end;

	pImagePtr = (unsigned char*)
		(pFwupgCtx->pImageData + sizeof(struct HpmfwupgImageHeader) +
		pImageHeader->oemDataLength + sizeof(unsigned char));

	actionsSize = pFwupgCtx->imageSize - sizeof(struct HpmfwupgImageHeader);
	if (!(option & VIEW_MODE)) {
		HpmDisplayUpgradeHeader();
	}

	while (( pImagePtr < (pFwupgCtx->pImageData + pFwupgCtx->imageSize -
					HPMFWUPG_MD5_SIGNATURE_LENGTH))
			&& (rc == HPMFWUPG_SUCCESS)) {

		pActionRecord = (struct HpmfwupgActionRecord*)pImagePtr;

		rc = HpmfwupgValidateActionRecordChecksum(pActionRecord);
		if (rc != HPMFWUPG_SUCCESS) {
			continue;
		}
		switch(pActionRecord->actionType) {
		case HPMFWUPG_ACTION_BACKUP_COMPONENTS:
			{
				if (!(option & COMPARE_MODE)) {

					struct HpmfwupgInitiateUpgradeActionCtx initUpgActionCmd;

					initUpgActionCmd.req.componentsMask.ComponentBits.byte =
						pFwupgCtx->compUpdateMask.ComponentBits.byte &
						pActionRecord->components.ComponentBits.byte;

					if (initUpgActionCmd.req.componentsMask.ComponentBits.byte) {
						initUpgActionCmd.req.upgradeAction  = HPMFWUPG_UPGRADE_ACTION_BACKUP;
						rc = HpmfwupgInitiateUpgradeAction(intf, &initUpgActionCmd, pFwupgCtx);
					}
				}
				pImagePtr+= sizeof(struct HpmfwupgActionRecord);
			}
			break;
		case HPMFWUPG_ACTION_PREPARE_COMPONENTS:
			{
				if (!(option & COMPARE_MODE)) {

					struct HpmfwupgInitiateUpgradeActionCtx initUpgActionCmd;

					initUpgActionCmd.req.componentsMask.ComponentBits.byte =
						pFwupgCtx->compUpdateMask.ComponentBits.byte &
						pActionRecord->components.ComponentBits.byte;
					if (initUpgActionCmd.req.componentsMask.ComponentBits.byte) {

						initUpgActionCmd.req.upgradeAction = HPMFWUPG_UPGRADE_ACTION_PREPARE;
						rc = HpmfwupgInitiateUpgradeAction(intf, &initUpgActionCmd, pFwupgCtx);
					}
				}
				pImagePtr+= sizeof(struct HpmfwupgActionRecord);
			}
			break;
		case HPMFWUPG_ACTION_UPLOAD_FIRMWARE:

			rc = HpmFwupgActionUploadFirmware(pActionRecord->components,
					pFwupgCtx,
					&pImagePtr,
					intf,
					option,
					&flagColdReset);
			break;
		default:
			lprintf(LOG_NOTICE, "    Invalid Action type. Cannot continue");
			rc = HPMFWUPG_ERROR;
			break;
		}
	}
	HpmDisplayLine("-", 79);
	fflush(stdout);
	lprintf(LOG_NOTICE, "(*) Component requires Payload Cold Reset");
	return rc;
}
