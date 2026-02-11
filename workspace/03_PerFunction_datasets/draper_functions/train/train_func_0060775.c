generate_plp_filename(ucs2_char_t* dst, const ucs2_char_t* extension, const ucs2_char_t* src, const ucs2_char_t* path_to_playlist, int playlist_in_music)
{
	if (playlist_in_music) {
		int i = 1;


		ucs2_char_t filename[MAX_PATH], basename[MAX_PATH];


		ucs2cpy(filename, src);
		filepathutil_strippath(filename);
		filepathutil_remove_extension(filename);


		filepathutil_combinepath(basename, sizeof(basename), path_to_playlist, filename);


		ucs2cpy(dst, basename);
		ucs2cat(dst, extension);
	} else {

		ucs2_char_t filename[MAX_PATH];
		ucs2cpy(filename, src);
		filepathutil_remove_extension(filename);
		ucs2cat(filename, extension);
		ucs2cpy(dst, filename);
	}
}
