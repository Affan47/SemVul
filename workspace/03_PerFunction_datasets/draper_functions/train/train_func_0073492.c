remove() {
    const String* txt = _namefe->text();
    if (txt->length() > 0) {
	Attribute* attr;
	if (attr = _list->GetAttr(txt->string())) {
	    _list->Remove(attr);
	    update_text(true);
	}
    }
}
