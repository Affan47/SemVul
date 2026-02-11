sc_cache_set (xlator_t *this, inode_t *inode, struct iatt *buf,
              const char *link)
{
	struct symlink_cache *sc = NULL;
	int                   ret = -1;
	int                   need_set = 0;


	symlink_inode_ctx_get (inode, this, VOID(&sc));
	if (!sc) {
		need_set = 1;
		sc = CALLOC (1, sizeof (*sc));
		if (!sc) {
			gf_log (this->name, GF_LOG_ERROR,
				"out of memory :(");
			goto err;
		}
	}

	if (sc->readlink) {
		gf_log (this->name, GF_LOG_DEBUG,
			"replacing old cache: %s with new cache: %s",
			sc->readlink, link);
		FREE (sc->readlink);
		sc->readlink = NULL;
	}

	if (link) {
		sc->readlink = strdup (link);
		if (!sc->readlink) {
			gf_log (this->name, GF_LOG_ERROR,
				"out of memory :(");
			goto err;
		}
	}

	sc->ctime = buf->ia_ctime;

	gf_log (this->name, GF_LOG_DEBUG,
		"setting symlink cache: %s", link);

	if (need_set) {
		ret = symlink_inode_ctx_set (inode, this, sc);

		if (ret < 0) {
			gf_log (this->name, GF_LOG_ERROR,
				"could not set inode context (%s)",
				strerror (-ret));
			goto err;
		}
	}

	return 0;
err:

	if (sc) {
		FREE (sc->readlink);
		sc->readlink = NULL;
		FREE (sc);
	}

	return -1;
}
