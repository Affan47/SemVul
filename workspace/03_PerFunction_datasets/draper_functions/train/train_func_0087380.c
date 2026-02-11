copyTo(const Path newpath, bool overwrite) const
		{
			File file1(newpath, getFileName());
			return copyTo(file1, overwrite);
		}
