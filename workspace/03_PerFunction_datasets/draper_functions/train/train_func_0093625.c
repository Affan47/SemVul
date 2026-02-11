Save()
{
	if (SaveType == T_ST_NONE) {
		return false;
	}

	if (SaveType & T_ST_INT) {
		int the_int =  atoi(Content.c_str());
		if (the_int <= SaveMax && the_int >= SaveMin) {
			*iSavePointer = the_int;
			return true;
		}
	} else if (SaveType & T_ST_SINT) {
		short the_sint =  (short)atoi(Content.c_str());
		if (the_sint <= SaveMax && the_sint >= SaveMin) {
			*siSavePointer = the_sint;
			return true;
		}
	} else if (SaveType & T_ST_FLOAT) {
		float the_float = (float)atof(Content.c_str());
		if (the_float <= flSaveMax && the_float >= flSaveMin) {
			*flSavePointer = the_float;
			return true;
		}
	} else if (SaveType & T_ST_CHAR) {
		size_t len = Content.length();
		if (SaveType & T_ST_NEW && len < uSaveMax) {
			if (*chpSavePointer != NULL) {
				delete[] *chpSavePointer;
			}

			*chpSavePointer = new char[len + 1];
			strcpy(*chpSavePointer, Content.c_str());
			return true;
		} else if (SaveType & T_ST_MALLOC && len < uSaveMax) {
			if (*chpSavePointer != NULL) {
				vm_free(*chpSavePointer);
			}

			*chpSavePointer = (char*)vm_malloc(sizeof(char) * (len + 1));
			strcpy(*chpSavePointer, Content.c_str());
			return true;
		} else if (len < uSaveMax) {
			strcpy(chSavePointer, Content.c_str());
			return true;
		}

	} else if (SaveType & T_ST_UBYTE) {
		int the_int = atoi(Content.c_str());
		if (the_int <= SaveMax && the_int >= SaveMin) {
			*ubSavePointer = (ubyte)the_int;
			return true;
		}
	}

	return false;
}
