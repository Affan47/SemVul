CreateCategory(
	Category_Struct *& category,
	const wxString& name,
	const CPath& path,
	const wxString& comment,
	uint32 color,
	uint8 prio)
{
	category = new Category_Struct();
	category->path = thePrefs::GetIncomingDir();
	uint32 cat = AddCat(category);
	return UpdateCategory(cat, name, path, comment, color, prio);
}
