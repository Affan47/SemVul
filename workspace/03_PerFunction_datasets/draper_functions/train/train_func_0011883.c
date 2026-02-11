process_lvol(struct ubi_device *ubi,
					    struct ubi_attach_info *ai,
					    struct ubi_ainf_volume *av)
{
	int err;
	struct rb_node *rb;
	struct ubi_ainf_peb *aeb;
	struct ubi_vtbl_record *leb[UBI_LAYOUT_VOLUME_EBS] = { NULL, NULL };
	int leb_corrupted[UBI_LAYOUT_VOLUME_EBS] = {1, 1};


	dbg_gen("check layout volume");


	ubi_rb_for_each_entry(rb, aeb, &av->root, u.rb) {
		leb[aeb->lnum] = vzalloc(ubi->vtbl_size);
		if (!leb[aeb->lnum]) {
			err = -ENOMEM;
			goto out_free;
		}

		err = ubi_io_read_data(ubi, leb[aeb->lnum], aeb->pnum, 0,
				       ubi->vtbl_size);
		if (err == UBI_IO_BITFLIPS || mtd_is_eccerr(err))


			aeb->scrub = 1;
		else if (err)
			goto out_free;
	}

	err = -EINVAL;
	if (leb[0]) {
		leb_corrupted[0] = vtbl_check(ubi, leb[0]);
		if (leb_corrupted[0] < 0)
			goto out_free;
	}

	if (!leb_corrupted[0]) {

		if (leb[1])
			leb_corrupted[1] = memcmp(leb[0], leb[1],
						  ubi->vtbl_size);
		if (leb_corrupted[1]) {
			ubi_warn(ubi, "volume table copy #2 is corrupted");
			err = create_vtbl(ubi, ai, 1, leb[0]);
			if (err)
				goto out_free;
			ubi_msg(ubi, "volume table was restored");
		}


		vfree(leb[1]);
		return leb[0];
	} else {

		if (leb[1]) {
			leb_corrupted[1] = vtbl_check(ubi, leb[1]);
			if (leb_corrupted[1] < 0)
				goto out_free;
		}
		if (leb_corrupted[1]) {

			ubi_err(ubi, "both volume tables are corrupted");
			goto out_free;
		}

		ubi_warn(ubi, "volume table copy #1 is corrupted");
		err = create_vtbl(ubi, ai, 0, leb[1]);
		if (err)
			goto out_free;
		ubi_msg(ubi, "volume table was restored");

		vfree(leb[0]);
		return leb[1];
	}

out_free:
	vfree(leb[0]);
	vfree(leb[1]);
	return ERR_PTR(err);
}
