CColorControl(gui::IGUIEnvironment* guiEnv, const core::position2d<s32> & pos, const wchar_t *text, IGUIElement* parent, s32 id=-1 )
		: gui::IGUIElement(gui::EGUIET_ELEMENT, guiEnv, parent,id, core::rect< s32 >(pos, pos+core::dimension2d<s32>(80, 75)))
		, DirtyFlag(true)
		, ColorStatic(0)
		, EditAlpha(0)
		, EditRed(0)
		, EditGreen(0)
		, EditBlue(0)
	{
		using namespace gui;
		ButtonSetId = makeUniqueId();

		const core::rect< s32 > rectControls(0,0,AbsoluteRect.getWidth(),AbsoluteRect.getHeight() );
		IGUIStaticText * groupElement =	guiEnv->addStaticText (L"", rectControls, true, false, this, -1, false);
		groupElement->setNotClipped(true);

		guiEnv->addStaticText (text, core::rect<s32>(0,0,80,15), false, false, groupElement, -1, false);

		EditAlpha = addEditForNumbers(guiEnv, core::position2d<s32>(0,15), L"a", -1, groupElement );
		EditRed = addEditForNumbers(guiEnv, core::position2d<s32>(0,30), L"r", -1, groupElement );
		EditGreen = addEditForNumbers(guiEnv, core::position2d<s32>(0,45), L"g", -1, groupElement );
		EditBlue = addEditForNumbers(guiEnv, core::position2d<s32>(0,60), L"b", -1, groupElement );

		ColorStatic = guiEnv->addStaticText (L"", core::rect<s32>(60,15,80,75), true, false, groupElement, -1, true);

		guiEnv->addButton (core::rect<s32>(60,35,80,50), groupElement, ButtonSetId, L"set");
		SetEditsFromColor(Color);
	}
