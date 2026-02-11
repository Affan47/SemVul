load_file_impl(xml_document& doc, FILE* file, unsigned int options, xml_encoding encoding)
	{
		if (!file) return make_parse_result(status_file_not_found);


		size_t size = 0;
		xml_parse_status size_status = get_file_size(file, size);

		if (size_status != status_ok)
		{
			fclose(file);
			return make_parse_result(size_status);
		}


		char* contents = static_cast<char*>(xml_memory::allocate(size > 0 ? size : 1));

		if (!contents)
		{
			fclose(file);
			return make_parse_result(status_out_of_memory);
		}


		size_t read_size = fread(contents, 1, size, file);
		fclose(file);

		if (read_size != size)
		{
			xml_memory::deallocate(contents);
			return make_parse_result(status_io_error);
		}

		return doc.load_buffer_inplace_own(contents, size, options, encoding);
	}
