GetFrameCompositionDescription(int ID3v2_FrameTypeID) {
	uint8_t matchingFrameDescription = 0;
	uint8_t total_frame_descrips = (uint8_t)(sizeof(FrameTypeConstructionList)/sizeof(*FrameTypeConstructionList));

	for (uint8_t i = 0; i < total_frame_descrips; i++) {
		if (FrameTypeConstructionList[i].ID3_FrameType == ID3v2_FrameTypeID) {
			matchingFrameDescription = i;
			break;
		}
	}
	return matchingFrameDescription;
}
