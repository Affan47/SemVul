ResourceManager_destroy() {
    if( rm ) {
        u32Array_destroy( &rm->mHashes );
        u32Array_destroy( &rm->mHandles );
        DEL_PTR( rm );
    }
}
