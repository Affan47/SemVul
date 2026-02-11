lf_pinbox_init(LF_PINBOX *pinbox, uint free_ptr_offset,
                    lf_pinbox_free_func *free_func, void *free_func_arg)
{
  DBUG_ASSERT(free_ptr_offset % sizeof(void *) == 0);
  compile_time_assert(sizeof(LF_PINS) == 64);
  lf_dynarray_init(&pinbox->pinarray, sizeof(LF_PINS));
  pinbox->pinstack_top_ver= 0;
  pinbox->pins_in_array= 0;
  pinbox->free_ptr_offset= free_ptr_offset;
  pinbox->free_func= free_func;
  pinbox->free_func_arg= free_func_arg;
}
