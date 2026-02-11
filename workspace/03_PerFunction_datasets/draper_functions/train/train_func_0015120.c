io_destroy_writer(io_Writer* writer)
{


	if(writer->fp != NULL)
	{

		io_flush_buffer(writer);

		fflush(writer->fp);

		fclose(writer->fp);
	}


	free(writer->buffer);
}
