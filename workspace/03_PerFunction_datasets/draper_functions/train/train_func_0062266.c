synctex_sheet_content(synctex_scanner_t scanner,int page) {
	if (scanner) {
		synctex_node_t sheet = scanner->sheet;
		while(sheet) {
			if (page == SYNCTEX_PAGE(sheet)) {
				return SYNCTEX_CHILD(sheet);
			}
			sheet = SYNCTEX_SIBLING(sheet);
		}
	}
	return NULL;
}
