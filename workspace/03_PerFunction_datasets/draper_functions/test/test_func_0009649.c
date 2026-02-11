nfs4_is_valid_delegation(const struct nfs_delegation *delegation,
		fmode_t flags)
{
	if (delegation != NULL && (delegation->type & flags) == flags &&
	    !test_bit(NFS_DELEGATION_REVOKED, &delegation->flags) &&
	    !test_bit(NFS_DELEGATION_RETURNING, &delegation->flags))
		return true;
	return false;
}
