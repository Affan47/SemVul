virtblk_get_id(struct gendisk *disk, char *id_str)
{
	struct virtio_blk *vblk = disk->private_data;
	struct request *req;
	struct bio *bio;
	int err;

	bio = bio_map_kern(vblk->disk->queue, id_str, VIRTIO_BLK_ID_BYTES,
			   GFP_KERNEL);
	if (IS_ERR(bio))
		return PTR_ERR(bio);

	req = blk_make_request(vblk->disk->queue, bio, GFP_KERNEL);
	if (IS_ERR(req)) {
		bio_put(bio);
		return PTR_ERR(req);
	}

	req->cmd_type = REQ_TYPE_DRV_PRIV;
	err = blk_execute_rq(vblk->disk->queue, vblk->disk, req, false);
	blk_put_request(req);

	return err;
}
