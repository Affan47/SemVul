VirtualAlloc(void *lpAddress, size_t dwSize, int flAllocationType,
        int flProtect) {
    write_log("- VirtualAlloc %p %zu %d %d\n", lpAddress, dwSize,
            flAllocationType, flProtect);
    if (flAllocationType & MEM_RESERVE) {
        write_log("  MEM_RESERVE\n");
    }
    if (flAllocationType & MEM_COMMIT) {
        write_log("  MEM_COMMIT\n");
    }
    if (flAllocationType & PAGE_READWRITE) {
        write_log("  PAGE_READWRITE\n");
    }
    int prot = 0;
    void *memory = NULL;

    if (flAllocationType == MEM_COMMIT && lpAddress == NULL) {
        memory = malloc(dwSize);
        if (memory == NULL) {
            write_log("memory allocated failed errno %d\n", errno);
        }
        return memory;
    }

    if (flAllocationType & MEM_RESERVE) {
        memory = malloc(dwSize);
        if (memory == NULL) {
            write_log("memory allocated failed errno %d\n", errno);
        }
#if 0
        memory = mmap(lpAddress, dwSize, prot, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        printf("mmap result: %p\n", memory);
        if (memory == (void *) -1) {
            printf("mmap failed errno %d\n", errno);
        }
#endif
    }
    else {
        memory = lpAddress;
    }

    if (flAllocationType & MEM_COMMIT) {
#if 0
        int lockresult = mlock(memory, dwSize);
        if (lockresult != 0) {
            printf("mlock failed errno %d\n", errno);
            perror("mlock failed");
        }
#endif
    }

    return memory;
}
