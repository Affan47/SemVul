cache_insert(struct cache_t *cp,
	     md_addr_t addr,
	     void *vp,
	     int nbytes,
	     tick_t now,
	     byte_t **udata,
	     md_addr_t *repl_addr,
	     enum duplicate_policy dup_policy)
{
  byte_t *p = vp;
  md_addr_t tag = CACHE_TAG(cp, addr);
  md_addr_t set = CACHE_SET(cp, addr);
  md_addr_t bofs = CACHE_BLK(cp, addr);
  struct cache_blk_t *repl;
  int lat = 0;

  cp->insertions++;


  repl = NULL;
  switch (dup_policy) {
    case DUP_KEEP_NEW:
    case DUP_KEEP_OLD:
      repl = cache_getBlock(cp, addr);
    case DUP_KEEP_BOTH:
      break;
    default:
      panic("bogus duplication policy");
  }
  if (dup_policy == DUP_KEEP_OLD && repl) {

    return lat;
  }

  if (!repl) {

    switch (cp->policy) {
    case LRU:
    case FIFO:
      repl = cp->sets[set].way_tail;
      update_way_list(&cp->sets[set], repl, Head);
      break;
    case Random:
      {
	int bindex = myrand() & (cp->assoc - 1);
	repl = CACHE_BINDEX(cp, cp->sets[set].blks, bindex);
      }
      break;
    default:
      panic("bogus replacement policy");
    }
  }


  if (cp->hsize)
    unlink_htab_ent(cp, &cp->sets[set], repl);


  cp->last_tagset = 0;
  cp->last_blk = NULL;


  if (repl->status & CACHE_BLK_VALID)
    {
      cp->replacements++;

      if (repl_addr)
	*repl_addr = CACHE_MK_BADDR(cp, repl->tag, set);


      lat += BOUND_POS(repl->ready - now);


      lat += BOUND_POS(cp->bus_free - (now + lat));


      cp->bus_free = MAX(cp->bus_free, (now + lat)) + 1;

      if (repl->status & CACHE_BLK_DIRTY)
	{

	  cp->writebacks++;
	  lat += cp->blk_access_fn(Write,
				   CACHE_MK_BADDR(cp, repl->tag, set),
				   cp->bsize, repl, now+lat);
	}
    }


  repl->tag = tag;
  repl->status = CACHE_BLK_VALID;


  lat += cp->blk_access_fn(Fetch, CACHE_BADDR(cp, addr), cp->bsize,
			   repl, now+lat);


  if (cp->balloc)
    {
      CACHE_BCOPY(Read, repl, bofs, p, nbytes);
    }


  if (udata)
    *udata = repl->user_data;


  repl->ready = now+lat;


  if (cp->hsize)
    link_htab_ent(cp, &cp->sets[set], repl);


  return lat;
}
