AddBinding()
{
	FCDMaterialInstanceBind* out = new FCDMaterialInstanceBind();
	bindings.push_back(out);
	SetNewChildFlag();
	return bindings.back();
}
