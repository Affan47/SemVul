ceph_mdsc_build_path(struct dentry *dentry, int *plen, u64 *base,
			   int stop_on_nosnap)
{
	struct dentry *temp;
	char *path;
	int len, pos;
	unsigned seq;

	if (dentry == NULL)
		return ERR_PTR(-EINVAL);

retry:
	len = 0;
	seq = read_seqbegin(&rename_lock);
	rcu_read_lock();
	for (temp = dentry; !IS_ROOT(temp);) {
		struct inode *inode = d_inode(temp);
		if (inode && ceph_snap(inode) == CEPH_SNAPDIR)
			len++;
		else if (stop_on_nosnap && inode &&
			 ceph_snap(inode) == CEPH_NOSNAP)
			break;
		else
			len += 1 + temp->d_name.len;
		temp = temp->d_parent;
	}
	rcu_read_unlock();
	if (len)
		len--;

	path = kmalloc(len+1, GFP_NOFS);
	if (path == NULL)
		return ERR_PTR(-ENOMEM);
	pos = len;
	path[pos] = 0;
	rcu_read_lock();
	for (temp = dentry; !IS_ROOT(temp) && pos != 0; ) {
		struct inode *inode;

		spin_lock(&temp->d_lock);
		inode = d_inode(temp);
		if (inode && ceph_snap(inode) == CEPH_SNAPDIR) {
			dout("build_path path+%d: %p SNAPDIR\n",
			     pos, temp);
		} else if (stop_on_nosnap && inode &&
			   ceph_snap(inode) == CEPH_NOSNAP) {
			spin_unlock(&temp->d_lock);
			break;
		} else {
			pos -= temp->d_name.len;
			if (pos < 0) {
				spin_unlock(&temp->d_lock);
				break;
			}
			strncpy(path + pos, temp->d_name.name,
				temp->d_name.len);
		}
		spin_unlock(&temp->d_lock);
		if (pos)
			path[--pos] = '/';
		temp = temp->d_parent;
	}
	rcu_read_unlock();
	if (pos != 0 || read_seqretry(&rename_lock, seq)) {
		pr_err("build_path did not end path lookup where "
		       "expected, namelen is %d, pos is %d\n", len, pos);


		kfree(path);
		goto retry;
	}

	*base = ceph_ino(d_inode(temp));
	*plen = len;
	dout("build_path on %p %d built %llx '%.*s'\n",
	     dentry, d_count(dentry), *base, len, path);
	return path;
}
