posix_fill_ino_from_gfid (xlator_t *this, struct iatt *buf)
{
        uint64_t temp_ino = 0;
        int j = 0;
        int i = 0;


        if (uuid_is_null (buf->ia_gfid)) {
                buf->ia_ino = -1;
                goto out;
        }
        for (i = 15; i > (15 - 8); i--) {
		temp_ino += (uint64_t)(buf->ia_gfid[i]) << j;
                j += 8;
        }
        buf->ia_ino = temp_ino;
out:
        return;
}
