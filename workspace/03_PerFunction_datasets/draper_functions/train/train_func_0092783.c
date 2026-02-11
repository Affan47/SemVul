cifs_compose_mount_options(const char *sb_mountdata,
				   const char *fullpath,
				   const struct dfs_info3_param *ref,
				   char **devname)
{
	int rc;
	char *mountdata = NULL;
	const char *prepath = NULL;
	int md_len;
	char *tkn_e;
	char *srvIP = NULL;
	char sep = ',';
	int off, noff;

	if (sb_mountdata == NULL)
		return ERR_PTR(-EINVAL);

	if (strlen(fullpath) - ref->path_consumed)
		prepath = fullpath + ref->path_consumed;

	*devname = cifs_build_devname(ref->node_name, prepath);
	if (IS_ERR(*devname)) {
		rc = PTR_ERR(*devname);
		*devname = NULL;
		goto compose_mount_options_err;
	}

	rc = dns_resolve_server_name_to_ip(*devname, &srvIP);
	if (rc < 0) {
		cifs_dbg(FYI, "%s: Failed to resolve server part of %s to IP: %d\n",
			 __func__, *devname, rc);
		goto compose_mount_options_err;
	}


	md_len = strlen(sb_mountdata) + INET6_ADDRSTRLEN;
	mountdata = kzalloc(md_len + 1, GFP_KERNEL);
	if (mountdata == NULL) {
		rc = -ENOMEM;
		goto compose_mount_options_err;
	}


	off = 0;
	if (strncmp(sb_mountdata, "sep=", 4) == 0) {
			sep = sb_mountdata[4];
			strncpy(mountdata, sb_mountdata, 5);
			off += 5;
	}

	do {
		tkn_e = strchr(sb_mountdata + off, sep);
		if (tkn_e == NULL)
			noff = strlen(sb_mountdata + off);
		else
			noff = tkn_e - (sb_mountdata + off) + 1;

		if (strncasecmp(sb_mountdata + off, "unc=", 4) == 0) {
			off += noff;
			continue;
		}
		if (strncasecmp(sb_mountdata + off, "ip=", 3) == 0) {
			off += noff;
			continue;
		}
		if (strncasecmp(sb_mountdata + off, "prefixpath=", 11) == 0) {
			off += noff;
			continue;
		}
		strncat(mountdata, sb_mountdata + off, noff);
		off += noff;
	} while (tkn_e);
	strcat(mountdata, sb_mountdata + off);
	mountdata[md_len] = '\0';


	if (mountdata[strlen(mountdata) - 1] != sep)
		strncat(mountdata, &sep, 1);
	strcat(mountdata, "ip=");
	strcat(mountdata, srvIP);


compose_mount_options_out:
	kfree(srvIP);
	return mountdata;

compose_mount_options_err:
	kfree(mountdata);
	mountdata = ERR_PTR(rc);
	kfree(*devname);
	*devname = NULL;
	goto compose_mount_options_out;
}
