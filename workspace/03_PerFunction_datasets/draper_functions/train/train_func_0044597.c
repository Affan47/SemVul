load_props(
    Style* s, const PropertyData* props, int priority
) {
    if (props != nil) {
	for (const PropertyData* p = &props[0]; p->path != nil; p++) {
	    s->attribute(String(p->path), String(p->value), priority);
	}
    }
}
