_resetValue() {
	if (valueType & VALUE_STRING) {
		TCHAR* t = static_cast<TCHAR*>(fieldsData);
		_CLDELETE_CARRAY(t);
	} else if (valueType & VALUE_READER) {
		Reader* r = static_cast<Reader*>(fieldsData);
		_CLDELETE(r);
	} else if (valueType & VALUE_BINARY) {
		ValueArray<uint8_t>* v = static_cast<ValueArray<uint8_t>*>(fieldsData);
		_CLDELETE(v);
	}
	valueType=VALUE_NONE;
}
