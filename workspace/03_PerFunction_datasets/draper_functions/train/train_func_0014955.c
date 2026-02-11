Union(const Geometry *other) const

{


	if ( isEmpty() ) return other->clone();
	if ( other->isEmpty() ) return clone();

	Geometry *out = NULL;

#ifdef SHORTCIRCUIT_PREDICATES


	if ( ! getEnvelopeInternal()->intersects(other->getEnvelopeInternal()) )
	{

		const GeometryCollection *coll;

		size_t ngeomsThis = getNumGeometries();
		size_t ngeomsOther = other->getNumGeometries();


		vector<Geometry *> *v = new vector<Geometry *>();
		v->reserve(ngeomsThis+ngeomsOther);


		if ( NULL != (coll = dynamic_cast<const GeometryCollection *>(this)) )
		{
			for (size_t i=0; i<ngeomsThis; ++i)
				v->push_back(coll->getGeometryN(i)->clone());
		} else {
			v->push_back(this->clone());
		}

		if ( NULL != (coll = dynamic_cast<const GeometryCollection *>(other)) )
		{
			for (size_t i=0; i<ngeomsOther; ++i)
				v->push_back(coll->getGeometryN(i)->clone());
		} else {
			v->push_back(other->clone());
		}

		out = factory->buildGeometry(v);
		return out;
	}
#endif

	return BinaryOp(this, other, overlayOp(OverlayOp::opUNION)).release();
}
