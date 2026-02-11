SetValueChange()
{
	SetValueChangedFlag();

	if (parent != NULL) parent->SetTransformsDirtyFlag();
}
