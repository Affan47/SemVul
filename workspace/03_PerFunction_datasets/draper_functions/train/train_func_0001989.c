SpinControl_Draw( menulist_s *s )
{
	char buffer[100];

	if ( s->generic.name )
	{
		Menu_DrawStringR2LDark( s->generic.x + s->generic.parent->x + LCOLUMN_OFFSET,
							s->generic.y + s->generic.parent->y,
							s->generic.name );
	}
	if ( !strchr( s->itemnames[s->curvalue], '\n' ) )
	{
		Menu_DrawString( RCOLUMN_OFFSET + s->generic.x + s->generic.parent->x, s->generic.y + s->generic.parent->y, s->itemnames[s->curvalue] );
	}
	else
	{
		strcpy( buffer, s->itemnames[s->curvalue] );
		*strchr( buffer, '\n' ) = 0;
		Menu_DrawString( RCOLUMN_OFFSET + s->generic.x + s->generic.parent->x, s->generic.y + s->generic.parent->y, buffer );
		strcpy( buffer, strchr( s->itemnames[s->curvalue], '\n' ) + 1 );
		Menu_DrawString( RCOLUMN_OFFSET + s->generic.x + s->generic.parent->x, s->generic.y + s->generic.parent->y + 10, buffer );
	}
}
