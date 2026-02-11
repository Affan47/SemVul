AddDevice(string DeviceName)
{
	uint32_t DeviceID;
	uint8_t TunerIndex;

	if (sscanf(DeviceName.c_str(), "%x-%hhu", &DeviceID, &TunerIndex) != 2) {
		return NULL;
	}

	return AddDevice(DeviceID, TunerIndex);
}
