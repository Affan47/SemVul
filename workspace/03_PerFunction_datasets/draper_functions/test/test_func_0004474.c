wb_ok(StackDecode *s, NODE *now, int width)
{
  if (now->seqnum <= s->maximum_filled_length) {


    return FALSE;
  } else {


    s->hypo_len_count[now->seqnum]++;
    if (s->hypo_len_count[now->seqnum] > width) {


      if (s->maximum_filled_length < now->seqnum) s->maximum_filled_length = now->seqnum;
    }
    return TRUE;
  }
}
