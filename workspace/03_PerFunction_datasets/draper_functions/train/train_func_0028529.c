SCSI_ProcessCmd(USB_OTG_CORE_HANDLE  *pdev,
					   uint8_t lun,
					   uint8_t *params) {
	cdev = pdev;

	switch (params[0]) {
		case SCSI_TEST_UNIT_READY:
			return SCSI_TestUnitReady(lun, params);

		case SCSI_REQUEST_SENSE:
			return SCSI_RequestSense (lun, params);
		case SCSI_INQUIRY:
			return SCSI_Inquiry(lun, params);

		case SCSI_START_STOP_UNIT:
			return SCSI_StartStopUnit(lun, params);

		case SCSI_ALLOW_MEDIUM_REMOVAL:
			return SCSI_StartStopUnit(lun, params);

		case SCSI_MODE_SENSE6:
			return SCSI_ModeSense6 (lun, params);

		case SCSI_MODE_SENSE10:
			return SCSI_ModeSense10 (lun, params);

		case SCSI_READ_FORMAT_CAPACITIES:
			return SCSI_ReadFormatCapacity(lun, params);

		case SCSI_READ_CAPACITY10:
			return SCSI_ReadCapacity10(lun, params);

		case SCSI_READ10:
			return SCSI_Read10(lun, params);

		case SCSI_WRITE10:
			return SCSI_Write10(lun, params);

		case SCSI_VERIFY10:
			return SCSI_Verify10(lun, params);

		default:
			SCSI_SenseCode(lun,
						   ILLEGAL_REQUEST,
						   INVALID_CDB);
			return -1;
	}
}
