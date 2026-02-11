Menu_Item_RightSize (menucommon_s *self, FNT_font_t font)
{
	menuvec2_t ret;
	ret.x = ret.y = 0;

	ret.y = font->height;

	if (self->name && (self->flags & QMF_RIGHT_COLUMN))
	{
		ret.x = Menu_PredictSize (self->name);
		if (self->type != MTYPE_TEXT)
			ret.x += RCOLUMN_OFFSET;
	}

	if (self->visible_length != 0)
		ret.x += font->width * self->visible_length + RCOLUMN_OFFSET;

	switch ( self->type )
	{
		case MTYPE_SLIDER:
			ret.x = font->width * LONGINPUT_SIZE + RCOLUMN_OFFSET;
			break;
		case MTYPE_FIELD:
			ret.y += 4;
			break;
		case MTYPE_SPINCONTROL:
			ret.x += SpinControl_MaxWidth ((menulist_s *)self);
			ret.y = SpinControl_MaxLines ((menulist_s *)self)*font->height;
			if (ret.y > font->height)
				ret.y += font->height-font->size;
			break;
		case MTYPE_SUBMENU:
			ret.y = Menu_TrueHeight(*(menuframework_s *)self);
			ret.x = CHASELINK(((menuframework_s *)self)->lwidth) +
					CHASELINK(((menuframework_s *)self)->rwidth);
			if (self->flags & QMF_SNUG_LEFT)
				ret.x -= CHASELINK(self->parent->lwidth);
			{
				menuvec2_t border = Menu_GetBorderSize ((menuframework_s*)self);
				if (ret.x < border.x + border.x/2)
					ret.x = border.x + border.x/2;
				ret.x += border.x;
				ret.y += border.y;
			}
			break;
		case MTYPE_ACTION:
		case MTYPE_TEXT:
			break;
	}

	if ((self->flags & QMF_BUTTON) && ret.x < CHASELINK(self->parent->rwidth) && !self->parent->horizontal)
		ret.x = CHASELINK(self->parent->rwidth);

	return ret;
}
