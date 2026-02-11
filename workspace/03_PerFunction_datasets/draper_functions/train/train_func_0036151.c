poolinit(struct memorypool *pool, int bytecount, int itemcount,
              int firstitemcount, int alignment)
#else
void poolinit(pool, bytecount, itemcount, firstitemcount, alignment)
struct memorypool *pool;
int bytecount;
int itemcount;
int firstitemcount;
int alignment;
#endif

{


  if (alignment > sizeof(void *)) {
    pool->alignbytes = alignment;
  } else {
    pool->alignbytes = sizeof(void *);
  }
  pool->itembytes = ((bytecount - 1) / pool->alignbytes + 1) *
                    pool->alignbytes;
  pool->itemsperblock = itemcount;
  if (firstitemcount == 0) {
    pool->itemsfirstblock = itemcount;
  } else {
    pool->itemsfirstblock = firstitemcount;
  }


  pool->firstblock = (void **)
    trimalloc(pool->itemsfirstblock * pool->itembytes + (int) sizeof(void *) +
              pool->alignbytes);

  *(pool->firstblock) = (void *) NULL;
  poolrestart(pool);
}
