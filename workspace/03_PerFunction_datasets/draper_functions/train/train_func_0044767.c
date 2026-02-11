mq_xattr_state (xlator_t *this,
                loc_t *loc,
                dict_t *dict,
                struct iatt buf)
{
        if (buf.ia_type == IA_IFREG ||
            buf.ia_type == IA_IFLNK) {
                mq_inspect_file_xattr (this, loc, dict, buf);
        } else if (buf.ia_type == IA_IFDIR)
                mq_inspect_directory_xattr (this, loc, dict, buf);

        return 0;
}
