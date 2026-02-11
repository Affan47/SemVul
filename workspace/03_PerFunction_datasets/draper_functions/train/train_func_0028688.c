VTGen_write_END_COLLECTIVE_OPERATION(VTGen* gen, uint64_t* time,
                                          uint64_t mid)
{
  VTGEN_CHECK(gen);

  if (VTGEN_IS_TRACE_ON(gen))
  {
    VTBuf_Entry_EndCollectiveOperation* new_entry;

    static const uint32_t length =
      VTGEN_ALIGN_LENGTH(sizeof(VTBuf_Entry_EndCollectiveOperation));

    VTGEN_ALLOC_EVENT(gen, length, time);

    new_entry = ((VTBuf_Entry_EndCollectiveOperation*)gen->buf->pos);

    new_entry->type   = VTBUF_ENTRY_TYPE__EndCollectiveOperation;
    new_entry->length = length;
    new_entry->time   = *time;
    new_entry->mid    = mid;

    VTGEN_JUMP(gen, length);
  }
}
