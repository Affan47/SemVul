createMultiPolygon(const vector<Geometry *> &fromPolys) const
{
	vector<Geometry *>*newGeoms = new vector<Geometry *>(fromPolys.size());
	for (size_t i=0; i<fromPolys.size(); i++)
	{
		(*newGeoms)[i] = fromPolys[i]->clone();
	}
	MultiPolygon *g = NULL;
	try {
		g = new MultiPolygon(newGeoms,this);
	} catch (...) {
		for (size_t i=0; i<newGeoms->size(); i++) {
			delete (*newGeoms)[i];
		}
		delete newGeoms;
		throw;
	}
	return g;
}
