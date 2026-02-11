Clone(FCDGeometrySpline* clone) const
{
	if (clone == NULL) clone = new FCDGeometrySpline(const_cast<FCDocument*>(GetDocument()), NULL);
	clone->type = type;


	for (FCDSplineContainer::const_iterator it = splines.begin(); it != splines.end(); ++it)
	{
		FCDSpline* cloneSpline = clone->AddSpline();
		(*it)->Clone(cloneSpline);
	}

	return clone;
}
