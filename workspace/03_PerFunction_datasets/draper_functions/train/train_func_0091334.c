ncp_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct inode *inode = file_inode(filp);
	struct ncp_server *server = NCP_SERVER(inode);
	kuid_t uid = current_uid();
	int need_drop_write = 0;
	long ret;

	switch (cmd) {
	case NCP_IOC_SETCHARSETS:
	case NCP_IOC_CONN_LOGGED_IN:
	case NCP_IOC_SETROOT:
		if (!capable(CAP_SYS_ADMIN)) {
			ret = -EPERM;
			goto out;
		}
		break;
	}
	if (!uid_eq(server->m.mounted_uid, uid)) {
		switch (cmd) {


		case NCP_IOC_GETOBJECTNAME:
		case NCP_IOC_SETOBJECTNAME:
		case NCP_IOC_GETPRIVATEDATA:
		case NCP_IOC_SETPRIVATEDATA:
#ifdef CONFIG_COMPAT
		case NCP_IOC_GETOBJECTNAME_32:
		case NCP_IOC_SETOBJECTNAME_32:
		case NCP_IOC_GETPRIVATEDATA_32:
		case NCP_IOC_SETPRIVATEDATA_32:
#endif
			ret = -EACCES;
			goto out;


		case NCP_IOC_GET_FS_INFO:
		case NCP_IOC_GET_FS_INFO_V2:
		case NCP_IOC_NCPREQUEST:
		case NCP_IOC_SETDENTRYTTL:
		case NCP_IOC_SIGN_INIT:
		case NCP_IOC_LOCKUNLOCK:
		case NCP_IOC_SET_SIGN_WANTED:
#ifdef CONFIG_COMPAT
		case NCP_IOC_GET_FS_INFO_V2_32:
		case NCP_IOC_NCPREQUEST_32:
#endif
			ret = mnt_want_write_file(filp);
			if (ret)
				goto out;
			need_drop_write = 1;
			ret = inode_permission(inode, MAY_WRITE);
			if (ret)
				goto outDropWrite;
			break;


		case NCP_IOC_GETMOUNTUID16:
		case NCP_IOC_GETMOUNTUID32:
		case NCP_IOC_GETMOUNTUID64:
		case NCP_IOC_GETROOT:
		case NCP_IOC_SIGN_WANTED:
			ret = inode_permission(inode, MAY_READ);
			if (ret)
				goto out;
			break;


		case NCP_IOC_GETCHARSETS:
		case NCP_IOC_GETDENTRYTTL:
		default:

		case NCP_IOC_SETCHARSETS:
		case NCP_IOC_CONN_LOGGED_IN:
		case NCP_IOC_SETROOT:
			break;
		}
	}
	ret = __ncp_ioctl(inode, cmd, arg);
outDropWrite:
	if (need_drop_write)
		mnt_drop_write_file(filp);
out:
	return ret;
}
