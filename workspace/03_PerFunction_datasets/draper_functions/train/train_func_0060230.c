repick(int depth, Hit& h) {
    Canvas* c = canvas();
    if (c != nil) {
	const Transformer& t = transformer();
	c->push_transform();
	c->transformer(t);
	h.push_transform();
	h.transform(t);
	pick(c, allocation(), depth, h);
	h.pop_transform();
	c->pop_transform();
    }
}
