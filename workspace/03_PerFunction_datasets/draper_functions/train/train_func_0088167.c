computeNormal() {
	for (vector<int>::const_iterator i = _triangles.begin();
			i < _triangles.end(); i++) {
		_normal += _parent->getTriangle(*i)->getNormal();
	}
	_normal.normalize();
}
