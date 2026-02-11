get_picture(const char *filename, Picture &picture, ::FLAC__StreamMetadata_Picture_Type type, const char *mime_type, const FLAC__byte *description, unsigned max_width, unsigned max_height, unsigned max_depth, unsigned max_colors)
		{
			FLAC__ASSERT(0 != filename);

			::FLAC__StreamMetadata *object;

			if(::FLAC__metadata_get_picture(filename, &object, type, mime_type, description, max_width, max_height, max_depth, max_colors)) {
				picture.assign(object, false);
				return true;
			}
			else
				return false;
		}
