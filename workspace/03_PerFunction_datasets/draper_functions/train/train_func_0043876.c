ceph_match_vxattr(struct inode *inode,
						const char *name)
{
	struct ceph_vxattr *vxattr = ceph_inode_vxattrs(inode);

	if (vxattr) {
		while (vxattr->name) {
			if (!strcmp(vxattr->name, name))
				return vxattr;
			vxattr++;
		}
	}

	return NULL;
}
