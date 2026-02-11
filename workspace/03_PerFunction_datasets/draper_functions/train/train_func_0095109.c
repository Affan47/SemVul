mlx4_ib_alloc_cq_buf(struct mlx4_ib_dev *dev, struct mlx4_ib_cq_buf *buf, int nent)
{
	int err;

	err = mlx4_buf_alloc(dev->dev, nent * dev->dev->caps.cqe_size,
			     PAGE_SIZE * 2, &buf->buf, GFP_KERNEL);

	if (err)
		goto out;

	buf->entry_size = dev->dev->caps.cqe_size;
	err = mlx4_mtt_init(dev->dev, buf->buf.npages, buf->buf.page_shift,
				    &buf->mtt);
	if (err)
		goto err_buf;

	err = mlx4_buf_write_mtt(dev->dev, &buf->mtt, &buf->buf, GFP_KERNEL);
	if (err)
		goto err_mtt;

	return 0;

err_mtt:
	mlx4_mtt_cleanup(dev->dev, &buf->mtt);

err_buf:
	mlx4_buf_free(dev->dev, nent * buf->entry_size, &buf->buf);

out:
	return err;
}
