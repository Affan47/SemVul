GetTransferCacheAtIndex(CTransfer*& transferPtr, int index) {
    try {
        transferPtr = m_TransferCache.at(index);
    } catch ( std::out_of_range ) {
        transferPtr = NULL;
        return -1;
    }

    return 0;
}
