xfs_getinfo(cdico *d, char *devname)
{
    struct xfs_sb sb;
    char uuid[512];
    u32 temp32;
    int ret=0;
    int fd;
    int res;

    if ((fd=open64(devname, O_RDONLY|O_LARGEFILE))<0)
    {   ret=-1;
        goto xfs_read_sb_return;
    }

    res=read(fd, &sb, sizeof(sb));
    if (res!=sizeof(sb))
    {   ret=-1;
        goto xfs_read_sb_close;
    }


    if (be32_to_cpu(sb.sb_magicnum) != XFS_SUPER_MAGIC)
    {   ret=-1;
        msgprintf(3, "sb.sb_magicnum!=XFS_SUPER_MAGIC\n");
        goto xfs_read_sb_close;
    }


    msgprintf(MSG_DEBUG1, "xfs_label=[%s]\n", sb.sb_fname);
    dico_add_string(d, 0, FSYSHEADKEY_FSLABEL, (char*)sb.sb_fname);


    memset(uuid, 0, sizeof(uuid));
    uuid_unparse_lower((u8*)&sb.sb_uuid, uuid);
    dico_add_string(d, 0, FSYSHEADKEY_FSUUID, uuid);
    msgprintf(MSG_DEBUG1, "xfs_uuid=[%s]\n", uuid);


    temp32=be32_to_cpu(sb.sb_blocksize);
    if ((temp32%512!=0) || (temp32<512) || (temp32>65536))
    {   ret=-1;
        msgprintf(3, "xfs_blksize=[%ld] is an invalid xfs block size\n", (long)temp32);
        goto xfs_read_sb_close;
    }
    dico_add_u64(d, 0, FSYSHEADKEY_FSXFSBLOCKSIZE, temp32);
    msgprintf(MSG_DEBUG1, "xfs_blksize=[%ld]\n", (long)temp32);


    dico_add_u64(d, 0, FSYSHEADKEY_MINFSAVERSION, FSA_VERSION_BUILD(0, 6, 4, 0));

xfs_read_sb_close:
    close(fd);
xfs_read_sb_return:
    return ret;
}
