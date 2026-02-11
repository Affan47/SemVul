destroy_mount_options(struct ceph_mount_options *args)
{
	dout("destroy_mount_options %p\n", args);
	kfree(args->snapdir_name);
	kfree(args);
}
