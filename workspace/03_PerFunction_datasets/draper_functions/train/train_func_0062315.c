ubi_eba_unmap_leb(struct ubi_device *ubi, struct ubi_volume *vol,
		      int lnum)
{
	int err, pnum, vol_id = vol->vol_id;

	if (ubi->ro_mode)
		return -EROFS;

	err = leb_write_lock(ubi, vol_id, lnum);
	if (err)
		return err;

	pnum = vol->eba_tbl[lnum];
	if (pnum < 0)

		goto out_unlock;

	dbg_eba("erase LEB %d:%d, PEB %d", vol_id, lnum, pnum);

	down_read(&ubi->fm_eba_sem);
	vol->eba_tbl[lnum] = UBI_LEB_UNMAPPED;
	up_read(&ubi->fm_eba_sem);
	err = ubi_wl_put_peb(ubi, vol_id, lnum, pnum, 0);

out_unlock:
	leb_write_unlock(ubi, vol_id, lnum);
	return err;
}
