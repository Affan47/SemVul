cache_evict_addr(struct cache_t *cp,
		 md_addr_t addr,
		 tick_t now)
{
  md_addr_t tag = CACHE_TAG(cp, addr);
  md_addr_t set = CACHE_SET(cp, addr);
  struct cache_blk_t *blk;
  int lat = cp->hit_latency;

  if (cp->hsize)
    {

      int hindex = CACHE_HASH(cp, tag);

      for (blk=cp->sets[set].hash[hindex];
	   blk;
	   blk=blk->hash_next)
	{
	  if (blk->tag == tag && (blk->status & CACHE_BLK_VALID))
	    break;
	}
    }
  else
    {

      for (blk=cp->sets[set].way_head;
	   blk;
	   blk=blk->way_next)
	{
	  if (blk->tag == tag && (blk->status & CACHE_BLK_VALID))
	    break;
	}
    }

  if (blk)
    {

      blk->status &= ~CACHE_BLK_VALID;


      cp->last_tagset = 0;
      cp->last_blk = NULL;


      update_way_list(&cp->sets[set], blk, Tail);
    }


  return lat;
}
