gfid_to_ino (uuid_t gfid)
{
	uint64_t  ino = 0;
	int       i = 0, j = 0;

        for (i = 15; i > (15 - 8); i--) {
                ino += (uint64_t)(gfid[i]) << j;
                j += 8;
        }

	return ino;
}
