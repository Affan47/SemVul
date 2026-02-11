glfs_graph_setup (struct glfs *fs, glusterfs_graph_t *graph)
{
	xlator_t      *new_subvol = NULL;
	xlator_t      *old_subvol = NULL;
	inode_table_t *itable = NULL;
	int            ret = -1;

	new_subvol = graph->top;


	pthread_mutex_lock (&fs->mutex);
	{
		if (new_subvol->switched ||
		    new_subvol == fs->active_subvol ||
		    new_subvol == fs->next_subvol) {

			ret = 0;
			goto unlock;
		}

		if (!new_subvol->itable) {
			itable = inode_table_new (131072, new_subvol);
			if (!itable) {
				errno = ENOMEM;
				ret = -1;
				goto unlock;
			}

			new_subvol->itable = itable;
		}

		old_subvol = fs->next_subvol;
		fs->next_subvol = new_subvol;
		fs->next_subvol->winds++;
		ret = 0;
	}
unlock:
	pthread_mutex_unlock (&fs->mutex);

	if (old_subvol)

		glfs_subvol_done (fs, old_subvol);

	return ret;
}
