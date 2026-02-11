get_file_hash_index(struct manifest *mf,
				    char *path,
				    struct file_hash *file_hash,
				    struct hashtable *mf_files,
				    struct hashtable *mf_file_infos)
{
	struct file_info fi;
	uint32_t *fi_index;
	uint32_t n;

	fi.index = get_include_file_index(mf, path, mf_files);
	memcpy(fi.hash, file_hash->hash, sizeof(fi.hash));
	fi.size = file_hash->size;

	fi_index = hashtable_search(mf_file_infos, &fi);
	if (fi_index) {
		return *fi_index;
	}

	n = mf->n_file_infos;
	mf->file_infos = x_realloc(mf->file_infos,
				   (n + 1) * sizeof(*mf->file_infos));
	mf->n_file_infos++;
	mf->file_infos[n] = fi;

	return n;
}
