walk_local_bvs (s48_call_t call,
		void (*func) (s48_call_t call, struct bv_group *bv, void *closure),
		void *closure)
{
  struct bv_group *b;

  for (b = call->local_bvs; b; b = b->next)
    func (call, b, closure);
}
