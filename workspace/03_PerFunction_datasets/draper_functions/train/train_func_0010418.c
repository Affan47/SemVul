WorldBound() const {
    BBox b;
    for (uint32_t i = 0; i < vertices.size(); i++)
        b = Union(b, (*ObjectToWorld)(vertices[i]->P));
    return b;
}
