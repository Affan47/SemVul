GC_should_collect(void)
{
    static word last_min_bytes_allocd;
    static word last_gc_no;
    if (last_gc_no != GC_gc_no) {
      last_gc_no = GC_gc_no;
      last_min_bytes_allocd = min_bytes_allocd();
    }
    return(GC_adj_bytes_allocd() >= last_min_bytes_allocd
           || GC_heapsize >= GC_collect_at_heapsize);
}
