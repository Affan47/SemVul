atomctrl_get_voltage_table_v3(
		struct pp_hwmgr *hwmgr,
		uint8_t voltage_type,
		uint8_t voltage_mode,
		pp_atomctrl_voltage_table *voltage_table)
{
	ATOM_VOLTAGE_OBJECT_INFO_V3_1 *voltage_info =
		(ATOM_VOLTAGE_OBJECT_INFO_V3_1 *)get_voltage_info_table(hwmgr->device);
	const ATOM_VOLTAGE_OBJECT_V3 *voltage_object;
	unsigned int i;

	PP_ASSERT_WITH_CODE((NULL != voltage_info),
			"Could not find Voltage Table in BIOS.", return -1;);

	voltage_object = atomctrl_lookup_voltage_type_v3
		(voltage_info, voltage_type, voltage_mode);

	if (voltage_object == NULL)
		return -1;

	PP_ASSERT_WITH_CODE(
			(voltage_object->asGpioVoltageObj.ucGpioEntryNum <=
			PP_ATOMCTRL_MAX_VOLTAGE_ENTRIES),
			"Too many voltage entries!",
			return -1;
			);

	for (i = 0; i < voltage_object->asGpioVoltageObj.ucGpioEntryNum; i++) {
		voltage_table->entries[i].value =
			voltage_object->asGpioVoltageObj.asVolGpioLut[i].usVoltageValue;
		voltage_table->entries[i].smio_low =
			voltage_object->asGpioVoltageObj.asVolGpioLut[i].ulVoltageId;
	}

	voltage_table->mask_low    =
		voltage_object->asGpioVoltageObj.ulGpioMaskVal;
	voltage_table->count      =
		voltage_object->asGpioVoltageObj.ucGpioEntryNum;
	voltage_table->phase_delay =
		voltage_object->asGpioVoltageObj.ucPhaseDelay;

	return 0;
}
