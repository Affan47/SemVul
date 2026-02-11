_TTF_RawPrint(
	FNT_font_t	font ,
	const char *	text ,
	unsigned int	text_length ,
	qboolean	r2l ,
	float		x ,
	float		y ,
	const float	color[4] )
{
	_TTF_font_t	fInternal = (_TTF_font_t) font->internal;

	if ( ! _TTF_CheckFlags( font ) )
		return;

	_TTF_PrepareToDraw( fInternal->texture );
	qglColor4fv( color );
	_TTF_RawPrintInternal( fInternal , text , text_length , r2l , x , y );
	_TTF_RestoreEnvironment( );
}
