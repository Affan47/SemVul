setDragMovingEnabled(bool setting)
{
	if (d_dragMovable != setting)
	{
		d_dragMovable = setting;

        getTitlebar()->setDraggingEnabled(setting);
    }

}
