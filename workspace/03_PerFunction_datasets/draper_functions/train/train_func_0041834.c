opengl_flush_frame_dump()
{
	char filename[MAX_FILENAME_LEN];

	Assert( GL_dump_buffer != NULL);

	for (int i = 0; i < GL_dump_frame_count; i++) {
		sprintf(filename, NOX("frm%04d.tga"), GL_dump_frame_number );
		GL_dump_frame_number++;

		CFILE *f = cfopen(filename, "wb", CFILE_NORMAL, CF_TYPE_DATA);


		cfwrite_ubyte( 0, f );
		cfwrite_ubyte( 0, f );
		cfwrite_ubyte( 2, f );
		cfwrite_ushort( 0, f );
		cfwrite_ushort( 0, f );
		cfwrite_ubyte( 0, f );
		cfwrite_ushort( 0, f );
		cfwrite_ushort( 0, f );
		cfwrite_ushort( (ushort)gr_screen.max_w, f );
		cfwrite_ushort( (ushort)gr_screen.max_h, f );
		cfwrite_ubyte( 24, f );
		cfwrite_ubyte( 0, f );

		glReadBuffer(GL_FRONT);
		glReadPixels(0, 0, gr_screen.max_w, gr_screen.max_h, GL_BGR_EXT, GL_UNSIGNED_BYTE, GL_dump_buffer);


		cfwrite( GL_dump_buffer, GL_dump_frame_size, 1, f );

		cfclose(f);

	}

	GL_dump_frame_count = 0;
}
