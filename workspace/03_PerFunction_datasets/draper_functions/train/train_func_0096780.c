coco_string_delete(wchar_t* &data) {
	delete [] data;
	data = NULL;
}
