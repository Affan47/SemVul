APar_TestVideoDescription(AtomicInfo* video_desc_atom, FILE* ISObmff_file) {
	uint16_t video_width = 0;
	uint16_t video_height = 0;
	uint16_t video_macroblocks = 0;
	uint8_t video_profile = 0;
	uint8_t video_level = 0;
	AtomicInfo* avcC_atom = NULL;

	if (ISObmff_file == NULL) return 0;

	char* avc1_contents = (char*)calloc(1, sizeof(char)* (size_t)video_desc_atom->AtomicLength);
	if (avc1_contents == NULL) {
		fclose(ISObmff_file);
		return 0;
	}

	APar_readX(avc1_contents, ISObmff_file, video_desc_atom->AtomicStart, video_desc_atom->AtomicLength);
	video_width = UInt16FromBigEndian(avc1_contents+32);
	video_height = UInt16FromBigEndian(avc1_contents+34);
	video_macroblocks = (video_width / 16) * (video_height / 16);

	avcC_atom = APar_FindChildAtom(video_desc_atom->AtomicNumber, "avcC");
	if (avcC_atom != NULL) {
		uint32_t avcC_offset = avcC_atom->AtomicStart - video_desc_atom->AtomicStart;
		video_profile = *(avc1_contents+avcC_offset+9);
		video_level = *(avc1_contents+avcC_offset+11);
	}

	if (video_profile == 66 && video_level <= 30) {
		if (video_macroblocks > 300 && video_macroblocks <= 1200) {

			if (video_level <= 30 && avcC_atom != NULL) {
				avcC_atom->AtomicData = (char*)calloc(1, sizeof(char)* (size_t)avcC_atom->AtomicLength);
				APar_readX(avcC_atom->AtomicData, ISObmff_file, avcC_atom->AtomicStart+8, avcC_atom->AtomicLength-8);
				if (video_macroblocks > 396 && video_macroblocks <= 792) {
					*(avcC_atom->AtomicData + 3) = 21;
				} else if (video_macroblocks > 792) {
					*(avcC_atom->AtomicData + 3) = 22;
				}
			}

			fclose(ISObmff_file);
			return video_macroblocks;
		} else {
			fprintf(stdout, "AtomicParsley warning: the AVC track macroblocks were not in the required range (300-1200). Skipping.\n");
		}
	} else {
		fprintf(stdout, "AtomicParsley warning: the AVC track profile/level was too high. The ipod hi-res uuid was not added.\n");
	}

	fclose(ISObmff_file);
	return 0;
}
