traceEventHeapInfo_ (CapsetID    heap_capset,
                          nat         gens,
                          W_        maxHeapSize,
                          W_        allocAreaSize,
                          W_        mblockSize,
                          W_        blockSize)
{
#ifdef DEBUG
    if (RtsFlags.TraceFlags.tracing == TRACE_STDERR) {

    } else
#endif
    {
        postEventHeapInfo(heap_capset, gens,
                          maxHeapSize, allocAreaSize,
                          mblockSize, blockSize);
    }
}
