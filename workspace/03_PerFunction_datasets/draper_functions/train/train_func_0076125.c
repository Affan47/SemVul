is_gfs2(struct gfs2_sbd *sdp)
{
	int fd, rc;
	struct gfs2_sb sb;

	fd = open(sdp->device_name, O_RDWR);
	if (fd < 0)
		return 0;

	rc = 0;
	if (lseek(fd, GFS2_SB_ADDR * GFS2_BASIC_BLOCK, SEEK_SET) >= 0 &&
	    read(fd, &sb, sizeof(sb)) == sizeof(sb) &&
	    be32_to_cpu(sb.sb_header.mh_magic) == GFS2_MAGIC &&
	    be32_to_cpu(sb.sb_header.mh_type) == GFS2_METATYPE_SB)
		rc = 1;
	close(fd);
	return rc;
}
