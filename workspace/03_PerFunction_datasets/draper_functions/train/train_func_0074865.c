GenCopyright() {
		FILE *file = NULL;

		if (coco_string_length(tab->frameDir) != 0) {
			wchar_t *copyFr = coco_string_create_append(tab->frameDir, L"/Copyright.frame");
			char *chCopyFr = coco_string_create_char(copyFr);
			file = fopen(chCopyFr, "r");
			delete [] copyFr;
			delete [] chCopyFr;
		}
		if (file == NULL) {
			wchar_t *copyFr = coco_string_create_append(tab->srcDir, L"Copyright.frame");
			char *chCopyFr = coco_string_create_char(copyFr);
			file = fopen(chCopyFr, "r");
			delete [] copyFr;
			delete [] chCopyFr;
		}
		if (file == NULL) {
			return;
		}

		FILE *scannerFram = fram;
		fram = file;

		CopyFramePart(NULL);
		fram = scannerFram;

		fclose(file);
	}
