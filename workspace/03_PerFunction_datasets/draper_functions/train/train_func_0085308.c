rocker_desc_err(const struct rocker_desc_info *desc_info)
{
	int err = desc_info->desc->comp_err & ~ROCKER_DMA_DESC_COMP_ERR_GEN;

	switch (err) {
	case ROCKER_OK:
		return 0;
	case -ROCKER_ENOENT:
		return -ENOENT;
	case -ROCKER_ENXIO:
		return -ENXIO;
	case -ROCKER_ENOMEM:
		return -ENOMEM;
	case -ROCKER_EEXIST:
		return -EEXIST;
	case -ROCKER_EINVAL:
		return -EINVAL;
	case -ROCKER_EMSGSIZE:
		return -EMSGSIZE;
	case -ROCKER_ENOTSUP:
		return -EOPNOTSUPP;
	case -ROCKER_ENOBUFS:
		return -ENOBUFS;
	}

	return -EINVAL;
}
