mlx4_get_slave_indx(struct mlx4_dev *dev, int vf)
{
	if ((vf < 0) || (vf >= dev->persist->num_vfs)) {
		mlx4_err(dev, "Bad vf number:%d (number of activated vf: %d)\n",
			 vf, dev->persist->num_vfs);
		return -EINVAL;
	}

	return vf+1;
}
