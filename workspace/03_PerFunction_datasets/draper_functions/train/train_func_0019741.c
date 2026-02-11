gsf_infile_zip_child_by_name (GsfInfile *infile, char const *name, GError **err)
{
	GsfInfileZip *zip = GSF_INFILE_ZIP (infile);
	GsfZipVDir *child_vdir = vdir_child_by_name (zip->vdir, name);

	if (child_vdir)
		return gsf_infile_zip_new_child (zip, child_vdir, err);

	return NULL;
}
