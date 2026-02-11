MakeAbsolute(const fstring& relativePath) const
{
	if (relativePath.empty()) return relativePath;
	FUUri uri(relativePath);

	MakeAbsolute(uri);
	return uri.GetAbsolutePath();
}
