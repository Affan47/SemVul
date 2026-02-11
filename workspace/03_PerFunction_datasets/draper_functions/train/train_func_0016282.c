lgfs2_rgrp_append(lgfs2_rgrps_t rgs, uint32_t rglen, int expand)
{
	int err = 0;
	lgfs2_rgrp_t rg = rgrp_insert(&rgs->root, rgs->nextaddr);
	if (rg == NULL)
		return NULL;

	rgs->curr_offset += rgs->align_off;
	if (rgs->curr_offset >= rgs->align)
		rgs->curr_offset = 0;

	if (rgs->rgsize > rglen)
		rglen = rgs->rgsize;

	rgs->nextaddr = align_block(rg->ri.ri_addr + rgs->rgsize, rgs->align) + rgs->curr_offset;

	if (expand && ((rgs->nextaddr - rg->ri.ri_addr) <= rgs->maxrgsz))
		rglen = rgs->nextaddr - rg->ri.ri_addr;

	if ((rgs->nextaddr + rgs->rgsize) > rgs->devlen) {

		if ((rgs->nextaddr < rgs->devlen) && ((rgs->devlen - rgs->nextaddr) >= rgs->minrgsz)) {
			rgs->rgsize = rgs->devlen - rgs->nextaddr;
		} else {
			if (rgs->devlen - rg->ri.ri_addr <= rgs->maxrgsz)
				rglen = rgs->devlen - rg->ri.ri_addr;
			else
				rglen = rgs->maxrgsz;

			rgs->nextaddr = 0;
		}
	}

	rg->ri.ri_length = rgblocks2bitblocks(rgs->bsize, rglen, &rg->ri.ri_data);
	rg->ri.ri_data0 = rg->ri.ri_addr + rg->ri.ri_length;
	rg->ri.ri_bitbytes = rg->ri.ri_data / GFS2_NBBY;
	rg->rg.rg_header.mh_magic = GFS2_MAGIC;
	rg->rg.rg_header.mh_type = GFS2_METATYPE_RG;
	rg->rg.rg_header.mh_format = GFS2_FORMAT_RG;
	rg->rg.rg_free = rg->ri.ri_data;

	err = gfs2_compute_bitstructs(rgs->bsize, rg);
	if (err != 0)
		return NULL;
	rgs->blks_total += rg->ri.ri_data;
	rgs->count++;
	return rg;
}
