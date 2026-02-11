attrCompare(BTKey* vLeft, BTKey* vRight) {
	HFSPlusAttrKey* left;
	HFSPlusAttrKey* right;
	uint16_t i;

	uint16_t cLeft;
	uint16_t cRight;

	left = (HFSPlusAttrKey*) vLeft;
	right =(HFSPlusAttrKey*) vRight;

	if(left->fileID < right->fileID) {
		return -1;
	} else if(left->fileID > right->fileID) {
		return 1;
	} else {
		for(i = 0; i < left->name.length; i++) {
			if(i >= right->name.length) {
				return 1;
			} else {
				cLeft = left->name.unicode[i];
				cRight = right->name.unicode[i];

				if(cLeft < cRight)
					return -1;
				else if(cLeft > cRight)
					return 1;
			}
		}

		if(i < right->name.length) {
			return -1;
		} else {


			return 0;
		}
	}
}
