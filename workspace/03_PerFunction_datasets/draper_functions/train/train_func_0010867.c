js_InitGC(JSRuntime *rt, uint32 maxbytes)
{
#if JS_GC_USE_MMAP
    if (js_gcArenasPerChunk == 0) {
        size_t cpuPageSize, arenasPerPage;
# if defined(XP_WIN)
        SYSTEM_INFO si;

        GetSystemInfo(&si);
        cpuPageSize = si.dwPageSize;

# elif defined(XP_UNIX) || defined(XP_BEOS)
        cpuPageSize = (size_t) sysconf(_SC_PAGESIZE);
# else
#  error "Not implemented"
# endif

        JS_ASSERT((cpuPageSize & (cpuPageSize - 1)) == 0);
        arenasPerPage = cpuPageSize >> GC_ARENA_SHIFT;
#ifdef DEBUG
        if (arenasPerPage == 0) {
            fprintf(stderr,
"JS engine warning: the size of the CPU page, %u bytes, is too low to use\n"
"paged allocation for the garbage collector. Please report this.\n",
                    (unsigned) cpuPageSize);
        }
#endif
        if (arenasPerPage - 1 <= (size_t) (GC_ARENAS_PER_CPU_PAGE_LIMIT - 1)) {


            js_gcUseMmap = JS_TRUE;
            js_gcArenasPerChunk = JS_MAX((uint32) arenasPerPage, 4);
        } else {
            js_gcUseMmap = JS_FALSE;
            js_gcArenasPerChunk = 7;
        }
    }
    JS_ASSERT(1 <= js_gcArenasPerChunk &&
              js_gcArenasPerChunk <= NO_FREE_ARENAS);
#endif

    InitGCArenaLists(rt);
    if (!JS_DHashTableInit(&rt->gcRootsHash, JS_DHashGetStubOps(), NULL,
                           sizeof(JSGCRootHashEntry), GC_ROOTS_SIZE)) {
        rt->gcRootsHash.ops = NULL;
        return JS_FALSE;
    }
    rt->gcLocksHash = NULL;


    rt->gcMaxBytes = rt->gcMaxMallocBytes = maxbytes;
    rt->gcEmptyArenaPoolLifespan = 30000;


    rt->setGCTriggerFactor((uint32) -1);


    rt->setGCLastBytes(8192);

    METER(memset(&rt->gcStats, 0, sizeof rt->gcStats));
    return JS_TRUE;
}
