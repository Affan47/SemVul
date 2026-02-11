set_attribute_get_filedir_parms_cb (GObject *source_object, GAsyncResult *res, gpointer user_data)
{
  GVfsAfpVolume *volume = G_VFS_AFP_VOLUME (source_object);
  GVfsJobSetAttribute *job = G_VFS_JOB_SET_ATTRIBUTE (user_data);

  GFileInfo *info;
  GError *err = NULL;

  guint32 uid, gid, permissions, ua_permissions;

  info = g_vfs_afp_volume_get_filedir_parms_finish (volume, res, &err);
  if (!info)
  {
    g_vfs_job_failed_from_error (G_VFS_JOB (job), err);
    g_error_free (err);
    return;
  }

  uid = g_file_info_get_attribute_uint32 (info, G_FILE_ATTRIBUTE_UNIX_UID);
  gid = g_file_info_get_attribute_uint32 (info, G_FILE_ATTRIBUTE_UNIX_GID);
  permissions = g_file_info_get_attribute_uint32 (info, G_FILE_ATTRIBUTE_UNIX_MODE);
  ua_permissions = g_file_info_get_attribute_uint32 (info, G_FILE_ATTRIBUTE_AFP_UA_PERMISSIONS);

  g_object_unref (info);


  if (strcmp (job->attribute, G_FILE_ATTRIBUTE_UNIX_UID) == 0)
    uid = job->value.uint32;
  else if (strcmp (job->attribute, G_FILE_ATTRIBUTE_UNIX_GID) == 0)
    gid = job->value.uint32;
  else if (strcmp (job->attribute, G_FILE_ATTRIBUTE_UNIX_MODE) == 0)
    permissions = job->value.uint32;

  g_vfs_afp_volume_set_unix_privs (volume, job->filename,
                                   uid, gid, permissions, ua_permissions,
                                   G_VFS_JOB (job)->cancellable,
                                   set_attribute_set_unix_privs_cb, job);
}
