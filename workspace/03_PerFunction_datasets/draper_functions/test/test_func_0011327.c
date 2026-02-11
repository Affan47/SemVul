InvertMouseFunc( void *_self )
{
	menulist_s *self = (menulist_s *)_self;
	if(self->curvalue && m_pitch->value > 0)
		Cvar_SetValue( "m_pitch", -m_pitch->value );
	else if(m_pitch->value < 0)
		Cvar_SetValue( "m_pitch", -m_pitch->value );
}
