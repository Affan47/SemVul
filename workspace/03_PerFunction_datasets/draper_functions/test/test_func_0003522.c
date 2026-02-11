vee_folder_rebuild_folder (CamelVeeFolder *vfolder,
                           CamelFolder *subfolder,
                           GCancellable *cancellable)
{
	CamelFolderChangeInfo *changes;
	CamelFolder *v_folder;

	v_folder = CAMEL_FOLDER (vfolder);
	changes = camel_folder_change_info_new ();

	camel_folder_freeze (v_folder);
	vee_folder_rebuild_folder_with_changes (vfolder, subfolder, changes, cancellable);
	camel_folder_thaw (v_folder);

	if (camel_folder_change_info_changed (changes))
		camel_folder_changed (CAMEL_FOLDER (vfolder), changes);
	camel_folder_change_info_free (changes);
}
