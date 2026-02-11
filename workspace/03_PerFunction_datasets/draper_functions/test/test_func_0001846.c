parseMovieClip(FILE *f)
{
	unsigned int clipID, frameNum = 0, framesTotal = 0;

	clipID = getWord(f);
	framesTotal = getWord(f);

	printf("\n");
	print("defineMovieClip %u // total frames: %u\n", clipID, framesTotal);
	indent++;

	while (!feof(f)) {
		unsigned int type;
		unsigned long int length;

		parseTagHeader(f, &type, &length);

		if (type == 0)
			break;

		switch (type) {
			case TAG_DOACTION:
				printFrameNum(frameNum);
				printActionBlock(f, length, AB_FRAME, frameNum, 0);
				print("end // of frame %u\n", frameNum);
				break;

			case TAG_PLACEOBJECT2:

				parsePlaceObject(f, length, TAG_PLACEOBJECT2);
				break;

			case TAG_PLACEOBJECT3:

				parsePlaceObject(f, length, TAG_PLACEOBJECT3);
				break;

			case TAG_SHOWFRAME:
				++frameNum;
				break;

			default:
				if (getTagString(type) == NULL) {
					print("\n");
					print("// unknown tag %lu length %li\n\n", type, length);
				}
				skipProtected(f, length);
		}
	}

	--indent;
	print("end // of defineMovieClip %u\n", clipID);
}
