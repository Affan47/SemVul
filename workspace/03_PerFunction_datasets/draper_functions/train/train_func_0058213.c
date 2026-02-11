icon_is_positioned (const NautilusCanvasIcon *icon)
{
	return icon->x != ICON_UNPOSITIONED_VALUE && icon->y != ICON_UNPOSITIONED_VALUE;
}
