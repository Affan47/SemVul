gsf_output_memory_vprintf (GsfOutput *output, char const *format, va_list args)
{
	GsfOutputMemory *mem = (GsfOutputMemory *)output;

	if (mem->buffer) {
		va_list args2;
		gsf_off_t len;


		G_VA_COPY (args2, args);

		len = g_vsnprintf (mem->buffer + output->cur_offset,
				   mem->capacity - output->cur_offset,
				   format, args);


		if (len >= (gsf_off_t)(mem->capacity - output->cur_offset))
			len = parent_class->Vprintf (output, format, args2);

		va_end (args2);

		return len;
	}
	return parent_class->Vprintf (output, format, args);
}
