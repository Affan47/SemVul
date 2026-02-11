checkOverwrite(FileName const & filename)
{
	if (!filename.exists())
		return 1;

	docstring text = bformat(_("The file %1$s already exists.\n\n"
				   "Do you want to overwrite that file?"),
				   makeDisplayPath(filename.absFileName()));
	return Alert::prompt(_("Overwrite file?"),
				text, 0, 3,
				_("&Keep file"), _("&Overwrite"),
				_("Overwrite &all"), _("&Cancel export"));
}
