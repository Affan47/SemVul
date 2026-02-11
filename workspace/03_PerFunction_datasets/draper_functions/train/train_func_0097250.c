statcmp(struct stat *s1, struct stat *s2, unsigned long type)
{
    int retval = 0;

    if (type & ST_DEV) {
        retval += s1->st_dev != s2->st_dev;
    }
    if (type & ST_INO) {
        retval += s1->st_ino != s2->st_ino;
    }
    if (type & ST_MODE) {
        retval += s1->st_mode != s2->st_mode;
    }
    if (type & ST_NLINK) {
        retval += s1->st_nlink != s2->st_nlink;
    }
    if (type & ST_UID) {
        retval += s1->st_uid != s2->st_uid;
    }
    if (type & ST_GID) {
        retval += s1->st_gid != s2->st_gid;
    }
    if (type & ST_RDEV) {
        retval += s1->st_rdev != s2->st_rdev;
    }
    if (type & ST_SIZE) {
        retval += s1->st_size != s2->st_size;
    }
    if (type & ST_BLKSIZE) {
        retval += s1->st_blksize != s2->st_blksize;
    }
    if (type & ST_BLOCKS) {
        retval += s1->st_blocks != s2->st_blocks;
    }
    if (type & ST_ATIME) {
        retval += s1->st_atime != s2->st_atime;
    }
    if (type & ST_MTIME) {
        retval += s1->st_mtime != s2->st_mtime;
    }
    if (type & ST_CTIME) {
        retval += s1->st_ctime != s2->st_ctime;
    }

    return retval;
}
