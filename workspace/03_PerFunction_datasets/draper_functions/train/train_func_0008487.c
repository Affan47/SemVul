exists(mode_t filter) const {
			bool existence = false;
			struct stat buf;
			string fpath = output(false);
			int result = stat(fpath.c_str(), &buf);
			if (result == 0 && (buf.st_mode & filter)) {
				existence = true;
			}
			return existence;
		}
