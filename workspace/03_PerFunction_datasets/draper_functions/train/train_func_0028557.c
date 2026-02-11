is_afr_lock_transaction (afr_local_t *local)
{
        int ret = 0;

        switch (local->transaction.type) {
        case AFR_DATA_TRANSACTION:
        case AFR_METADATA_TRANSACTION:
                ret = 1;
                break;

        case AFR_ENTRY_RENAME_TRANSACTION:
        case AFR_ENTRY_TRANSACTION:
                ret = 0;
                break;

        }

        return ret;
}
