handleEnterNotify(XCrossingEvent *e)
{
	if(curr)
	{
		hideSubmenus();

		selectMenuItem( xmenuselect_color.pixel );

		if(curr->sub)
		{
			testMenuEdgeDetect(curr->sub);

			if(curr->sub->right_edge)
			{
				if(curr->sub->bottom_edge)
				{
					showSub(curr->sub, x - curr->sub->width - 1,
					yres - curr->sub->height);
				}
				else
					showSub(curr->sub,
						x - curr->sub->width - 1,
						y + curr->item_y - item_height + 5
						);

				}
			else {
				if(curr->sub->bottom_edge)
				{
					showSub(curr->sub,
							x + width + 1,
							xres - curr->sub->height + item_height
						);

				}
				else {
					showSub(curr->sub,
						x + width + 1,
						y + curr->item_y - item_height + 5
						);
				}
			}
		}
		redraw(curr);
	}
}
