ToolTypeEvent(GtkWidget * widget)
{
	if (GTK_TOGGLE_BUTTON(buttonBrush)->active)
		activeTool = TOOL_BRUSH;
	else if (GTK_TOGGLE_BUTTON(buttonLine)->active)
		activeTool = TOOL_LINE;
	else if (GTK_TOGGLE_BUTTON(buttonRectangle)->active)
		activeTool = TOOL_RECTANGLE;
	else if (GTK_TOGGLE_BUTTON(buttonFilledRectangle)->active)
		activeTool = TOOL_FILLED_RECTANGLE;

	return 0;
}
