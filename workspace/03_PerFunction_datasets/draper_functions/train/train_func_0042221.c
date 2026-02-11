setUnifiedConstraintArea(const URect* area)
{
    const Rect renderer_area(Vector2(0, 0),
                          System::getSingleton().getRenderer()->getDisplaySize());

	if (area)
	{
        d_constraints = *area;
	}
	else
	{
		d_constraints.d_min.d_x = cegui_reldim(renderer_area.d_left / renderer_area.getWidth());
		d_constraints.d_min.d_y = cegui_reldim(renderer_area.d_top / renderer_area.getHeight());
		d_constraints.d_max.d_x = cegui_reldim(renderer_area.d_right / renderer_area.getWidth());
		d_constraints.d_max.d_y = cegui_reldim(renderer_area.d_bottom / renderer_area.getHeight());
	}

	constrainPosition();
}
