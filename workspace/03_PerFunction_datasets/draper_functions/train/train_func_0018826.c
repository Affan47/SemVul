setTransparency()
{
	irr::gui::IGUISkin * skin = MenuDevice->getGUIEnvironment()->getSkin();

	for (u32 i=0; i<gui::EGDC_COUNT ; ++i)
	{
		video::SColor col = SkinColor[i];

		if (false == transparent)
			col.setAlpha(255);

		skin->setColor((gui::EGUI_DEFAULT_COLOR)i, col);
	}
}
