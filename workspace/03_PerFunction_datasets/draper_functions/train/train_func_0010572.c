gr_opengl_config_buffer(const int buffer_id, vertex_buffer *vb)
{
	if (Cmdline_nohtl) {
		return false;
	}

	if (buffer_id < 0) {
		return false;
	}

	Assert( buffer_id < (int)GL_vertex_buffers.size() );

	if (vb == NULL) {
		return false;
	}

	if ( !(vb->flags & VB_FLAG_POSITION) ) {
		Int3();
		return false;
	}

	opengl_vertex_buffer *m_vbp = &GL_vertex_buffers[buffer_id];


	vb->stride = 0;


	Verify( vb->model_list->vert != NULL );
	vb->stride += (3 * sizeof(GLfloat));


	if (vb->flags & VB_FLAG_NORMAL) {
		Verify( vb->model_list->norm != NULL );
		vb->stride += (3 * sizeof(GLfloat));
	}


	if (vb->flags & VB_FLAG_UV1) {
		vb->stride += (2 * sizeof(GLfloat));
	}


	if (vb->flags & VB_FLAG_TANGENT) {
		Assert( Cmdline_normal );

		Verify( vb->model_list->tsb != NULL );
		vb->stride += (4 * sizeof(GLfloat));
	}


	vb->vertex_offset = m_vbp->vbo_size;
	m_vbp->vbo_size += vb->stride * vb->model_list->n_verts;

	for (size_t idx = 0; idx < vb->tex_buf.size(); idx++) {
		buffer_data *bd = &vb->tex_buf[idx];

		bd->index_offset = m_vbp->ibo_size;
		m_vbp->ibo_size += bd->n_verts * ((bd->flags & VB_FLAG_LARGE_INDEX) ? sizeof(uint) : sizeof(ushort));
	}

	return true;
}
