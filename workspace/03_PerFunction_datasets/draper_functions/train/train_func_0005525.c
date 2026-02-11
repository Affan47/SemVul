previewModeToggle(bool state)
{

	if (state)
	{

		int diff = updateFileInfoOnChangeMode(GLESettings::PreviewMode);
		drawingArea->setEditMode(false);


		enableEditModeToolBars(false);


		emit toolSelected(GLEDrawingArea::NoTool);


		if (drawingArea->thereAreNewObjects())
		{
			updateGLE();
			if (settings->saveOnPreview())
			{
				save();
			}
			drawingArea->clearNewObjectsFlag();
			renderGLE();
		}
		else
		{
			if (diff == 0) refreshDisplay();
			else if (diff == 1) renderEPS();
			else renderGLE();
		}
	}
}
