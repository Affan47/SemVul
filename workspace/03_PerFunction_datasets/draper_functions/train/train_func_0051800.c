Clone(FCDEntityInstance* _clone) const
{
	FCDMaterialInstance* clone = NULL;
	if (_clone == NULL) clone = new FCDMaterialInstance(const_cast<FCDocument*>(GetDocument()), NULL);
	else if (!_clone->HasType(FCDMaterialInstance::GetClassType())) return Parent::Clone(_clone);
	else clone = (FCDMaterialInstance*) _clone;

	Parent::Clone(clone);


	clone->semantic = semantic;
	size_t bindingCount = bindings.size();
	for (size_t b = 0; b < bindingCount; ++b)
	{
		const FCDMaterialInstanceBind* bind = bindings[b];
		clone->AddBinding(*bind->semantic, *bind->target);
	}
	bindingCount = vertexBindings.size();
	for (size_t b = 0; b < bindingCount; ++b)
	{
		const FCDMaterialInstanceBindVertexInput* bind = vertexBindings[b];
		clone->AddVertexInputBinding(*bind->semantic, (FUDaeGeometryInput::Semantic) *bind->inputSemantic, *bind->inputSet);
	}
	return clone;
}
