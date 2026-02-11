pick(Canvas* c, const Allocation& a, int depth, Hit& h) {
    Transformer t(transformer_);
    transform(t, a, natural_allocation_);
    c->push_transform();
    c->transform(t);
    h.push_transform();
    h.transform(t);
    MonoGlyph::pick(c, natural_allocation_, depth, h);
    c->pop_transform();
    h.pop_transform();
}
