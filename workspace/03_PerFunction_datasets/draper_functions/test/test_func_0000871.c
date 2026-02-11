call_spmproc_a(unsigned long length_on_u, unsigned long length_on_v,
    unsigned long unit_edist, bool suffix_of_u, void *data)
{
  struct Data *d = data;
  if (suffix_of_u)
    d->proc_a(d->u->seqnum, d->v->seqnum, length_on_u, length_on_v,
              unit_edist, d->u->direct, d->v->direct, d->procdata);
  else
    d->proc_a(d->v->seqnum, d->u->seqnum, length_on_v, length_on_u,
              unit_edist, d->v->direct, d->u->direct, d->procdata);
}
