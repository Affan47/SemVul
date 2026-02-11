OpenGen(const wchar_t *genName) {
		wchar_t *fn = coco_string_create_append(tab->outDir, genName);
		char *chFn = coco_string_create_char(fn);

		if ((gen = fopen(chFn, "r")) != NULL) {
			fclose(gen);
			wchar_t *oldName = coco_string_create_append(fn, L".old");
			char *chOldName = coco_string_create_char(oldName);
			remove(chOldName); rename(chFn, chOldName);
			coco_string_delete(chOldName);
			coco_string_delete(oldName);
		}
		if ((gen = fopen(chFn, "w")) == NULL) {
			wchar_t *message = coco_string_create_append(L"-- Cannot generate : ", genName);
			errors->Exception(message);
			delete [] message;
		}
		coco_string_delete(chFn);
		coco_string_delete(fn);

		return gen;
	}
