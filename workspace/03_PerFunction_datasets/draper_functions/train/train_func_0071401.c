xtSplitRoot(FILE *dev_ptr,
		       struct dinode *ip,
		       struct xtree_buf *xroot,
		       int64_t offset, int nblocks, int64_t blkno)
{
	xtpage_t *rootpage;
	xtpage_t *newpage;
	int64_t xaddr;
	int nextindex;
	xad_t *xad;
	int rc = 0;
	struct xtree_buf *newbuf;
	int xlen;


	newbuf = malloc(sizeof (struct xtree_buf));
	if (newbuf == NULL) {
		message_user(MSG_OSO_INSUFF_MEMORY, NULL, 0, OSO_MSG);
		return (ENOMEM);
	}
	newbuf->up = xroot;
	if (xroot->down == NULL) {
		badblock_pages = newbuf;
	} else {
		xroot->down->up = newbuf;
	}
	newbuf->down = xroot->down;
	xroot->down = newbuf;
	newpage = newbuf->page = malloc(PSIZE);
	if (newpage == NULL) {
		message_user(MSG_OSO_INSUFF_MEMORY, NULL, 0, OSO_MSG);
		return (ENOMEM);
	}


	xlen = 1 << control_page->dn_l2nbperpage;
	if ((rc = dbAlloc(dev_ptr, xlen, &xaddr)))
		return rc;

	rootpage = xroot->page;


	newpage->header.flag =
	    (rootpage->header.flag & BT_LEAF) ? BT_LEAF : BT_INTERNAL;
	PXDlength(&(newpage->header.self), xlen);
	PXDaddress(&(newpage->header.self), xaddr);
	newpage->header.nextindex = XTENTRYSTART;
	newpage->header.maxentry = PSIZE >> L2XTSLOTSIZE;


	newpage->header.next = 0;
	newpage->header.prev = 0;


	nextindex = rootpage->header.maxentry;
	memcpy(&newpage->xad[XTENTRYSTART], &rootpage->xad[XTENTRYSTART],
	       (nextindex - XTENTRYSTART) << L2XTSLOTSIZE);


	xad = &newpage->xad[nextindex];
	XADoffset(xad, offset);
	XADlength(xad, nblocks);
	XADaddress(xad, blkno);


	newpage->header.nextindex = nextindex + 1;


	xad = &rootpage->xad[XTENTRYSTART];
	XADoffset(xad, 0);
	XADlength(xad, xlen);
	XADaddress(xad, xaddr);


	rootpage->header.flag &= ~BT_LEAF;
	rootpage->header.flag |= BT_INTERNAL;

	rootpage->header.nextindex = XTENTRYSTART + 1;


	ip->di_nblocks += xlen;

	return 0;
}
