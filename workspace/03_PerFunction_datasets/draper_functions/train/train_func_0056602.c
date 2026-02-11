mf_hash_find(mht, key)
    mf_hashtab_T    *mht;
    blocknr_T	    key;
{
    mf_hashitem_T   *mhi;

    mhi = mht->mht_buckets[key & mht->mht_mask];
    while (mhi != NULL && mhi->mhi_key != key)
	mhi = mhi->mhi_next;

    return mhi;
}
