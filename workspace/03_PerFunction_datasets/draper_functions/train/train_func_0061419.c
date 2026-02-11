utm_hasCapacity(UToolMemory *mem, int32_t capacity) {
    if(mem->capacity<capacity) {
        int32_t newCapacity;

        if(mem->maxCapacity<capacity) {
            fprintf(stderr, "error: %s - trying to use more than maxCapacity=%ld units\n",
                    mem->name, (long)mem->maxCapacity);
            exit(U_MEMORY_ALLOCATION_ERROR);
        }


        if(capacity>=2*mem->capacity) {
            newCapacity=capacity;
        } else if(mem->capacity<=mem->maxCapacity/3) {
            newCapacity=2*mem->capacity;
        } else {
            newCapacity=mem->maxCapacity;
        }

        if(mem->array==mem->staticArray) {
            mem->array=uprv_malloc(newCapacity*mem->size);
            if(mem->array!=NULL) {
                uprv_memcpy(mem->array, mem->staticArray, mem->idx*mem->size);
            }
        } else {
            mem->array=uprv_realloc(mem->array, newCapacity*mem->size);
        }

        if(mem->array==NULL) {
            fprintf(stderr, "error: %s - out of memory\n", mem->name);
            exit(U_MEMORY_ALLOCATION_ERROR);
        }
        mem->capacity=newCapacity;
    }

    return TRUE;
}
