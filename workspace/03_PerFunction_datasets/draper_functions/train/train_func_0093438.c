realColor() const
{
	if (paint_color_ != Color_none)
		return paint_color_;
	if (color_ == Color_none)
		return Color_foreground;
	return color_;
}
