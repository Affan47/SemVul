getCreateableGUIElementType(s32 idx) const
{
	if (idx>=0 && idx<EGUIET_COUNT)
		return (EGUI_ELEMENT_TYPE)idx;

	return EGUIET_ELEMENT;
}
