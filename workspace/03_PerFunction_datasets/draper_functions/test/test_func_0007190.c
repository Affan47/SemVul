SetType(FUDaeSplineType::Type _type)
{
	while (!splines.empty()) splines.back()->Release();
	type = _type;
	SetDirtyFlag();
	return true;
}
