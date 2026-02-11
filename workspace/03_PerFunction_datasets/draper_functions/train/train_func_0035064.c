setSprite(EGUI_BUTTON_STATE state, s32 index, video::SColor color, bool loop)
{
	if (SpriteBank)
	{
		ButtonSprites[(u32)state].Index	= index;
		ButtonSprites[(u32)state].Color	= color;
		ButtonSprites[(u32)state].Loop	= loop;
	}
	else
	{
		ButtonSprites[(u32)state].Index = -1;
	}
}
