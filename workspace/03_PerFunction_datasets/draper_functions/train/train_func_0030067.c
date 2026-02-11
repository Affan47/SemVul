opengl_shader_set_current(opengl_shader_t *shader_obj)
{
	if (shader_obj != NULL) {
		if(!Current_shader || (Current_shader->program_id != shader_obj->program_id)) {
			Current_shader = shader_obj;
			vglUseProgramObjectARB(Current_shader->program_id);

#ifndef NDEBUG
			if ( opengl_check_for_errors("shader_set_current()") ) {
				vglValidateProgramARB(Current_shader->program_id);

				GLint obj_status = 0;
				vglGetObjectParameterivARB(Current_shader->program_id, GL_OBJECT_VALIDATE_STATUS_ARB, &obj_status);

				if ( !obj_status ) {
					opengl_shader_check_info_log(Current_shader->program_id);

					mprintf(("VALIDATE INFO-LOG:\n"));

					if (strlen(GLshader_info_log) > 5) {
						mprintf(("%s\n", GLshader_info_log));
					} else {
						mprintf(("<EMPTY>\n"));
					}
				}
			}
#endif
		}
	} else {
		Current_shader = NULL;
		vglUseProgramObjectARB(0);
	}
}
