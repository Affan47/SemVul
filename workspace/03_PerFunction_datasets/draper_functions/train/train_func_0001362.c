Clone(FCDEntity* _clone, bool cloneChildren) const
{
	FCDImage* clone = NULL;
	if (_clone == NULL) _clone = clone = new FCDImage(const_cast<FCDocument*>(GetDocument()));
	else if (_clone->HasType(FCDImage::GetClassType())) clone = (FCDImage*) _clone;

	FCDEntity::Clone(_clone, cloneChildren);

	if (clone != NULL)
	{
		clone->width = width;
		clone->height = height;
		clone->depth = depth;
		clone->filename = filename;
		clone->SetVideoFlag(GetVideoFlag());
	}
	return _clone;
}
