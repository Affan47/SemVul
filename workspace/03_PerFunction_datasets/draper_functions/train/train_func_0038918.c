F(code, v0, v1)
int code;
int v0, v1;
{
   u_int hash;
   int val;
   struct valnode *p;

   hash = (u_int)code ^ (v0 << 4) ^ (v1 << 8);
   hash %= MODULUS;

   for (p = hashtbl[hash]; p; p = p->next)
      if (p->code == code && p->v0 == v0 && p->v1 == v1)
         return p->val;

   val = ++curval;
   if (BPF_MODE(code) == BPF_IMM &&
       (BPF_CLASS(code) == BPF_LD || BPF_CLASS(code) == BPF_LDX)) {
      vmap[val].const_val = v0;
      vmap[val].is_const = 1;
   }
   p = next_vnode++;
   p->val = val;
   p->code = code;
   p->v0 = v0;
   p->v1 = v1;
   p->next = hashtbl[hash];
   hashtbl[hash] = p;

   return val;
}
