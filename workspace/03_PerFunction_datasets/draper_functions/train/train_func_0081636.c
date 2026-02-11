DisableClientTexture()
{
	if ( client_texture_units[active_client_texture_unit].status == GL_FALSE ) {
		return;
	}

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	client_texture_units[active_client_texture_unit].status = GL_FALSE;
}
