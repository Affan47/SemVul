fcpdev_edd_describe ( struct fcp_device *fcpdev,
				 struct edd_interface_type *type,
				 union edd_device_path *path ) {
	union {
		struct fc_name fc;
		uint64_t u64;
	} wwn;
	union {
		struct scsi_lun scsi;
		uint64_t u64;
	} lun;

	type->type = cpu_to_le64 ( EDD_INTF_TYPE_FIBRE );
	memcpy ( &wwn.fc, &fcpdev->wwn, sizeof ( wwn.fc ) );
	path->fibre.wwn = be64_to_cpu ( wwn.u64 );
	memcpy ( &lun.scsi, &fcpdev->lun, sizeof ( lun.scsi ) );
	path->fibre.lun = be64_to_cpu ( lun.u64 );
	return 0;
}
