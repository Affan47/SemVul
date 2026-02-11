configureScrollbars(void)
{
    Scrollbar* vertScrollbar = getVertScrollbar();
    Scrollbar* horzScrollbar = getHorzScrollbar();

	float totalHeight	= getTotalItemsHeight();
	float widestItem	= getWidestItemWidth();


	if ((totalHeight > getListRenderArea().getHeight()) || d_forceVertScroll)
	{
		vertScrollbar->show();


		if ((widestItem > getListRenderArea().getWidth()) || d_forceHorzScroll)
		{
			horzScrollbar->show();
		}
		else
		{
			horzScrollbar->hide();
		}

	}
	else
	{

		if ((widestItem > getListRenderArea().getWidth()) || d_forceHorzScroll)
		{
			horzScrollbar->show();


			if ((totalHeight > getListRenderArea().getHeight()) || d_forceVertScroll)
			{
				vertScrollbar->show();
			}
			else
			{
				vertScrollbar->hide();
			}

		}
		else
		{
			vertScrollbar->hide();
			horzScrollbar->hide();
		}

	}


	Rect renderArea(getListRenderArea());

	vertScrollbar->setDocumentSize(totalHeight);
	vertScrollbar->setPageSize(renderArea.getHeight());
	vertScrollbar->setStepSize(ceguimax(1.0f, renderArea.getHeight() / 10.0f));
	vertScrollbar->setScrollPosition(vertScrollbar->getScrollPosition());

	horzScrollbar->setDocumentSize(widestItem);
	horzScrollbar->setPageSize(renderArea.getWidth());
	horzScrollbar->setStepSize(ceguimax(1.0f, renderArea.getWidth() / 10.0f));
	horzScrollbar->setScrollPosition(horzScrollbar->getScrollPosition());
}
