CGUICheckBox(bool checked, IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle)
: IGUICheckBox(environment, parent, id, rectangle), checkTime(0), Pressed(false), Checked(checked)
{
	#ifdef _DEBUG
	setDebugName("CGUICheckBox");
	#endif


	setTabStop(true);
	setTabOrder(-1);
}
