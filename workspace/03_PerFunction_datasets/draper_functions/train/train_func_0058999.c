Begin(GB_PAINT *d)
{
	void *device = d->device;
	QPaintDevice *target = NULL;

	if (GB.Is(device, CLASS_Picture))
	{
		QPixmap *pixmap = ((CPICTURE *)device)->pixmap;

		if (pixmap->isNull())
		{
			GB.Error("Bad picture");
			return TRUE;
		}

		target = pixmap;
	}
	else if (GB.Is(device, CLASS_Image))
	{
		QImage *image = CIMAGE_get((CIMAGE *)device);

		if (image->isNull())
		{
			GB.Error("Bad image");
			return TRUE;
		}

		target = image;
	}
	else if (GB.Is(device, CLASS_DrawingArea))
	{
		MyDrawingArea *wid;

		wid = (MyDrawingArea *)(((CWIDGET *)device)->widget);

		if (wid->isCached())
			target = wid->getBackgroundPixmap();
		else if (wid->cache)
			target = wid->cache;
		else
		{
			if (!wid->inDrawEvent())
			{
				GB.Error("Cannot paint outside of Draw event handler");
				return TRUE;
			}

			target = wid;
		}

		wid->drawn++;

		if (init_painting(d, target))
			return TRUE;

		d->width = wid->width();
		d->height = wid->height();
		return FALSE;
	}
	else if (GB.Is(device, CLASS_Printer))
	{
		CPRINTER *printer = (CPRINTER *)device;

		if (!printer->printing)
		{
			GB.Error("Printer is not printing");
			return TRUE;
		}

		target = printer->printer;
	}
	else if (GB.Is(device, CLASS_SvgImage))
	{
		CSVGIMAGE *svgimage = (CSVGIMAGE *)device;
		target = SVGIMAGE_begin(svgimage, &EXTRA(d)->painter);
		if (!target)
		{
			GB.Error("SvgImage size is not defined");
			return TRUE;
		}
	}

	return init_painting(d, target);
}
