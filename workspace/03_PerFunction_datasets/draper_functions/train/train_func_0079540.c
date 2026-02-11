addScrollBar(bool horizontal, const core::rect<s32>& rectangle, IGUIElement* parent, s32 id)
{
	IGUIScrollBar* bar = new CGUIScrollBar(horizontal, this, parent ? parent : this, id, rectangle);
	bar->drop();
	return bar;
}
