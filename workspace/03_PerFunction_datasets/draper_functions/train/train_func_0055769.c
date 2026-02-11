zpoints() const {
    if (!_z && !_y && !_x && !is_empty()) ((TopoFace*)this)->load_points();
    return _z;
}
