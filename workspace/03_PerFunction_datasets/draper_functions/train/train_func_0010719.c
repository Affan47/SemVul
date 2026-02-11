xdebug_end_emit (MonoImageWriter *w, MonoDwarfWriter *dw, MonoMethod *method)
{
	guint8 *img;
	guint32 img_size;
	struct jit_code_entry *entry;
	guint64 *psize;

	il_file_line_index = mono_dwarf_writer_get_il_file_line_index (dw);
	mono_dwarf_writer_close (dw);

	img_writer_emit_writeout (w);

	img = img_writer_get_output (w, &img_size);

	img_writer_destroy (w);

	if (FALSE) {

		FILE *fp;
		char *file_name;
		static int file_counter;

		file_counter ++;
		file_name = g_strdup_printf ("xdb-%d.o", file_counter);
		printf ("%s %p %d\n", file_name, img, img_size);

		fp = fopen (file_name, "w");
		fwrite (img, img_size, 1, fp);
		fclose (fp);
		g_free (file_name);
	}


	entry = g_malloc0 (sizeof (struct jit_code_entry));

	entry->symfile_addr = (const char*)img;
	psize = (guint64*)&entry->symfile_size1;
	*psize = img_size;

	entry->next_entry = __jit_debug_descriptor.first_entry;
	if (__jit_debug_descriptor.first_entry)
		__jit_debug_descriptor.first_entry->prev_entry = entry;
	__jit_debug_descriptor.first_entry = entry;

	__jit_debug_descriptor.relevant_entry = entry;
	__jit_debug_descriptor.action_flag = JIT_REGISTER_FN;

	__jit_debug_register_code ();
}
