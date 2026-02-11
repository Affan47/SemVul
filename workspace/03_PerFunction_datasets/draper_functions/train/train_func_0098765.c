test_lf_alloc(void *arg)
{
  int    m= (*(int *)arg)/2;
  int32 x,y= 0;
  LF_PINS *pins;

  if (with_my_thread_init)
    my_thread_init();

  pins= lf_alloc_get_pins(&lf_allocator);

  for (x= ((int)(intptr)(&m)); m ; m--)
  {
    TLA *node1, *node2;
    x= (x*m+0x87654321) & INT_MAX32;
    node1= (TLA *)lf_alloc_new(pins);
    node1->data= x;
    y+= node1->data;
    node1->data= 0;
    node2= (TLA *)lf_alloc_new(pins);
    node2->data= x;
    y-= node2->data;
    node2->data= 0;
    lf_alloc_free(pins, node1);
    lf_alloc_free(pins, node2);
  }
  lf_alloc_put_pins(pins);
  pthread_mutex_lock(&mutex);
  bad+= y;

  if (--N == 0)
  {
    diag("%d mallocs, %d pins in stack",
         lf_allocator.mallocs, lf_allocator.pinbox.pins_in_array);
#ifdef MY_LF_EXTRA_DEBUG
    bad|= lf_allocator.mallocs - lf_alloc_pool_count(&lf_allocator);
#endif
  }
  if (!--running_threads) pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);

  if (with_my_thread_init)
    my_thread_end();
  return 0;
}
