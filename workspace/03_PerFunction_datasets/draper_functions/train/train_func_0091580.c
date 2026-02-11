addkey(unsigned long sector,unsigned char *key)
{
	KeyStorage::Node n,nu;
	int x,y,z;


	y = -1;
	x = (readkey(root,&n) >= 0) ? root : (-1);
	z = max_block;

	while (x >= 0) {
		y = x;

		if (readkey(x,&n) < 0) {
			bitch(BITCHWARNING,"KeyStorage::addkey......readkey failed for block %u. Sector %u not added to tree",x,sector);
			return -1;
		}

		if (sector < n.sector)	x = n.left;
		else			x = n.right;


		if (x == 0) x = -1;
	}

	nu.left =	0;
	nu.right =	0;
	nu.sector =	sector;
	memcpy(nu.key,key,8);
	if (writekey(z,&nu) < 0) {
		bitch(BITCHWARNING,"KeyStorage::addkey......writeblock failed for block %u. Sector %u was not added to tree",z,sector);
		return -1;
	}

	if (y < 0) {
		if (setroot(z) < 0) {
			bitch(BITCHWARNING,"KeyStorage::addkey......setroot(%u) failed for sector %u",z,sector);
			return -1;
		}
	}
	else {
		if (readkey(y,&n) < 0) {
			bitch(BITCHWARNING,"KeyStorage::addkey......readkey failed for block %u. Sector %u was not added to tree",y,sector);
			return -1;
		}

		if (sector < n.sector)	n.left = z;
		else			n.right = z;

		if (writekey(y,&n) < 0) {
			bitch(BITCHWARNING,"KeyStorage::addkey......writekey failed for block %u. Sector %u was not added",y,sector);
			return -1;
		}
	}

	return 0;
}
