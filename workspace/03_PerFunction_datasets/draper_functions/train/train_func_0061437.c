gc_mark(void * ptr)
{
    GC_Heap *gh;
    Header *hdr;


    if (!(gh = is_pointer_to_heap(ptr))) return;
    if (!(hdr = get_header(gh, ptr))) return;
    if (!FL_TEST(hdr, FL_ALLOC)) return;
    if (FL_TEST(hdr, FL_MARK)) return;


    FL_SET(hdr, FL_MARK);
    DEBUG(printf("mark ptr : %p, header : %p\n", ptr, hdr));


    gc_mark_range((void *)(hdr+1), (void *)NEXT_HEADER(hdr));
}
