do_async_file_ops() {
    if (async_copies.size()) {
        ASYNC_COPY* acp = async_copies[0];
        if (acp->copy_chunk()) {
            async_copies.erase(async_copies.begin());
            delete acp;
        }
        return true;
    }
    if (async_verifies.size()) {
        if (async_verifies[0]->verify_chunk()) {
            async_verifies.erase(async_verifies.begin());
        }
        return true;
    }
    return false;
}
