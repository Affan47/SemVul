accept_editor(FieldEditor*) {
    Coord v;
    const String& value = *editor_->text();
    if (value.convert(v)) {
	bvalue_->current_value(v);
    }
}
