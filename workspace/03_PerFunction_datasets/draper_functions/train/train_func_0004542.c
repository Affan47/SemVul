smb_mnt_get_fsinfo(unsigned int xid, struct cifs_tcon *tcon,
				void __user *arg)
{
	int rc = 0;
	struct smb_mnt_fs_info *fsinf;

	fsinf = kzalloc(sizeof(struct smb_mnt_fs_info), GFP_KERNEL);
	if (fsinf == NULL)
		return -ENOMEM;

	fsinf->version = 1;
	fsinf->protocol_id = tcon->ses->server->vals->protocol_id;
	fsinf->device_characteristics =
			le32_to_cpu(tcon->fsDevInfo.DeviceCharacteristics);
	fsinf->device_type = le32_to_cpu(tcon->fsDevInfo.DeviceType);
	fsinf->fs_attributes = le32_to_cpu(tcon->fsAttrInfo.Attributes);
	fsinf->max_path_component =
		le32_to_cpu(tcon->fsAttrInfo.MaxPathNameComponentLength);
#ifdef CONFIG_CIFS_SMB2
	fsinf->vol_serial_number = tcon->vol_serial_number;
	fsinf->vol_create_time = le64_to_cpu(tcon->vol_create_time);
	fsinf->share_flags = tcon->share_flags;
	fsinf->share_caps = le32_to_cpu(tcon->capabilities);
	fsinf->sector_flags = tcon->ss_flags;
	fsinf->optimal_sector_size = tcon->perf_sector_size;
	fsinf->max_bytes_chunk = tcon->max_bytes_chunk;
	fsinf->maximal_access = tcon->maximal_access;
#endif
	fsinf->cifs_posix_caps = le64_to_cpu(tcon->fsUnixInfo.Capability);

	if (copy_to_user(arg, fsinf, sizeof(struct smb_mnt_fs_info)))
		rc = -EFAULT;

	kfree(fsinf);
	return rc;
}
