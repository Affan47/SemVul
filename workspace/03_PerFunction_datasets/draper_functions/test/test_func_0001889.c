setDataFPValue(const uint64_t outputSettings, const double *data, uint16_t offset, const uint16_t numValues)
{
	for (uint16_t i=0; i<numValues; i++) {
		switch (outputSettings & CMT_OUTPUTSETTINGS_DATAFORMAT_MASK)
		{
			case CMT_OUTPUTSETTINGS_DATAFORMAT_FLOAT:
				setDataFloat((float)data[i], offset);
				offset += 4;
				break;

			case CMT_OUTPUTSETTINGS_DATAFORMAT_DOUBLE:
				setDataDouble(data[i], offset);
				offset += 8;
				break;

			case CMT_OUTPUTSETTINGS_DATAFORMAT_FP1632:
				setDataFP1632(data[i], offset);
				offset += 6;
				break;

			case CMT_OUTPUTSETTINGS_DATAFORMAT_F1220:
				setDataF1220(data[i], offset);
				offset += 4;
		}
	}
}
