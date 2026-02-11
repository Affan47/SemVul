draw( bool refresh )
{
	if( refresh || invalid )
	{

		if( invalid )
			getBackground();
		else
			memcpy( image, background, render->getSize() );


		if( pid && icon->isExclusive() )
			render->activeMark( (unsigned char *) image,
				dock->getMarkType(), dock->getMarkLeft(), dock->getMarkTop() );


		if( fading < Complete )
			render->ghosted( (unsigned char *) image,
				(unsigned char *) normalicon, fading );
		else
			render->opaque( (unsigned char *) image,
				(unsigned char *) normalicon );
	}

	XPutImage( dock->getDisplay(), window, dock->getGC(), surface, 0, 0,
		left, top, width, height );
}
