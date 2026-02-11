flint_stack_release_small(void)
{
   if (block_left == FLINT_SMALL_BLOCK_SIZE - 2)
   {
      block_ptr -= 2;
      block_left = block_ptr[0];
      mp_limb_t * temp = block_ptr;
      block_ptr = (mp_limb_t *) block_ptr[1];
      flint_heap_free(temp);
   }

   block_ptr--;
   unsigned long temp = (*block_ptr);
   block_left += (temp+1);
   block_ptr -= temp;
}
