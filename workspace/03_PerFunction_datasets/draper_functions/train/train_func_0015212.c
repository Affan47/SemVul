VTGen_write_ENTER_STAT(VTGen* gen, uint64_t* time)
{
  VTGEN_CHECK(gen);

  if (VTGEN_IS_TRACE_ON(gen))
  {
    VTBuf_Entry_EnterLeave* new_entry;

    static const uint32_t length =
      VTGEN_ALIGN_LENGTH(sizeof(VTBuf_Entry_EnterLeave));

    VTGEN_ALLOC_EVENT(gen, length, time);

    new_entry = ((VTBuf_Entry_EnterLeave*)gen->buf->pos);

    new_entry->type   = VTBUF_ENTRY_TYPE__Enter;
    new_entry->length = length;
    new_entry->time   = *time;
    new_entry->rid    = vt_trc_regid[VT__TRC_STAT];
    new_entry->sid    = 0;

    VTGEN_JUMP(gen, length);
  }
}
