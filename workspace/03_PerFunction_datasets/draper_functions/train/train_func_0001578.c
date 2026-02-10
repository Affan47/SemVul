reallocate() {
    Canvas* c = canvas_;
    if (c != nil) {

	Requisition s;
	request(s);

	c->push_transform();
	c->transformer(transformer_);
	extension_.clear();
	allocate(c, allocation_, extension_);
	c->pop_transform();
    }
}
