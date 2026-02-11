mca_allocator_bucket_alloc(
    mca_allocator_base_module_t * mem,
    size_t size,
    mca_mpool_base_registration_t** registration)
{
    mca_allocator_bucket_t * mem_options = (mca_allocator_bucket_t *) mem;

    int bucket_num = 0;
    size_t bucket_size = MCA_ALLOCATOR_BUCKET_1_SIZE;
    size_t allocated_size;
    mca_allocator_bucket_chunk_header_t * chunk;
    mca_allocator_bucket_chunk_header_t * first_chunk;
    mca_allocator_bucket_segment_head_t * segment_header;

    size += sizeof(mca_allocator_bucket_chunk_header_t);


    while(size > bucket_size) {
        bucket_num++;
        bucket_size <<= 1;
    }


    OPAL_THREAD_LOCK(&(mem_options->buckets[bucket_num].lock));

    if(NULL != mem_options->buckets[bucket_num].free_chunk) {
        chunk = mem_options->buckets[bucket_num].free_chunk;
        mem_options->buckets[bucket_num].free_chunk = chunk->u.next_free;
        chunk->u.bucket = bucket_num;

        chunk += 1;

        OPAL_THREAD_UNLOCK(&(mem_options->buckets[bucket_num].lock));
        return((void *) chunk);
    }

    allocated_size = bucket_size;


    allocated_size += sizeof(mca_allocator_bucket_segment_head_t);

    segment_header = (mca_allocator_bucket_segment_head_t *)
                   mem_options->get_mem_fn(mem_options->super.alc_mpool, &allocated_size, registration);
    if(NULL == segment_header) {

        OPAL_THREAD_UNLOCK(&(mem_options->buckets[bucket_num].lock));
        return(NULL);
    }


    allocated_size -= (sizeof(mca_allocator_bucket_segment_head_t) + bucket_size);
    chunk = first_chunk = segment_header->first_chunk =
                  (mca_allocator_bucket_chunk_header_t *) (segment_header + 1);

    segment_header->next_segment = mem_options->buckets[bucket_num].segment_head;
    mem_options->buckets[bucket_num].segment_head = segment_header;
    if(allocated_size >= bucket_size) {
        mem_options->buckets[bucket_num].free_chunk =
                        (mca_allocator_bucket_chunk_header_t *) ((char *) chunk + bucket_size);
        chunk->next_in_segment = (mca_allocator_bucket_chunk_header_t *)
                                   ((char *)chunk + bucket_size);
        while(allocated_size >= bucket_size) {
            chunk = (mca_allocator_bucket_chunk_header_t *) ((char *) chunk + bucket_size);
            chunk->u.next_free = (mca_allocator_bucket_chunk_header_t *)
                                 ((char *) chunk + bucket_size);
            chunk->next_in_segment = chunk->u.next_free;
            allocated_size -= bucket_size;
        }
        chunk->next_in_segment = first_chunk;
        chunk->u.next_free = NULL;
    } else {
        first_chunk->next_in_segment = first_chunk;
    }
    first_chunk->u.bucket = bucket_num;
    OPAL_THREAD_UNLOCK(&(mem_options->buckets[bucket_num].lock));

    return((void *) (first_chunk + 1));
}
