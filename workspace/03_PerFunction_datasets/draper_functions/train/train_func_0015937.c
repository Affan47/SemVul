border_context_to_parts(
	int context)
{
	if (context == C_FRAME || context == C_SIDEBAR ||
	    context == (C_FRAME | C_SIDEBAR))
	{
		return PART_FRAME;
	}
	else if (context == C_F_TOPLEFT)
	{
		return PART_BORDER_NW;
	}
	else if (context == C_F_TOPRIGHT)
	{
		return PART_BORDER_NE;
	}
	else if (context == C_F_BOTTOMLEFT)
	{
		return PART_BORDER_SW;
	}
	else if (context == C_F_BOTTOMRIGHT)
	{
		return PART_BORDER_SE;
	}
	else if (context == C_SB_LEFT)
	{
		return PART_BORDER_W;
	}
	else if (context == C_SB_RIGHT)
	{
		return PART_BORDER_E;
	}
	else if (context == C_SB_TOP)
	{
		return PART_BORDER_N;
	}
	else if (context == C_SB_BOTTOM)
	{
		return PART_BORDER_S;
	}
	else if (context == C_TITLE)
	{
		return PART_TITLE;
	}
	else if (context & (C_LALL | C_RALL))
	{
		return PART_BUTTONS;
	}

	return PART_NONE;
}
