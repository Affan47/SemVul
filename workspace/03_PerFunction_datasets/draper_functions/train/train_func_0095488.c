mdc_inode_iatt_set_validate(xlator_t *this, inode_t *inode, struct iatt *prebuf,
			    struct iatt *iatt)
{
        int              ret = -1;
        struct md_cache *mdc = NULL;

        mdc = mdc_inode_prep (this, inode);
        if (!mdc)
                goto out;

        LOCK (&mdc->lock);
        {
                if (!iatt || !iatt->ia_ctime) {
                        mdc->ia_time = 0;
                        goto unlock;
                }


		if (IA_ISREG(inode->ia_type) &&
		    ((iatt->ia_mtime != mdc->md_mtime) ||
		    (iatt->ia_ctime != mdc->md_ctime)))
			if (!prebuf || (prebuf->ia_ctime != mdc->md_ctime) ||
			    (prebuf->ia_mtime != mdc->md_mtime))
				inode_invalidate(inode);

                mdc_from_iatt (mdc, iatt);

                time (&mdc->ia_time);
        }
unlock:
        UNLOCK (&mdc->lock);
        ret = 0;
out:
        return ret;
}
