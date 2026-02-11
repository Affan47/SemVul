default_values(GLint unit, GLenum target)
{
	vglActiveTextureARB(GL_TEXTURE0 + unit);

	if (target == GL_INVALID_ENUM) {
		if (unit < GL_supported_texture_units) {
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_TEXTURE_CUBE_MAP);
		}

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		units[unit].texture_target = GL_TEXTURE_2D;
		units[unit].texture_id = 0;
	}
}
