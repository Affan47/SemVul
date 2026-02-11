reserveOutputSpace(omni::alignment_t align,size_t required)
{
  if (pd_readonly_and_external_buffer)
    OMNIORB_THROW(MARSHAL,MARSHAL_AttemptToWriteToReadOnlyBuf,
		  (CORBA::CompletionStatus)completion());


  required += omni::align_to((omni::ptr_arith_t)pd_outb_mkr,align) -
              (omni::ptr_arith_t)pd_outb_mkr;

  size_t newsize = (char*)pd_outb_end - (char*)pd_outb_mkr;
  if (newsize > required)
    return 1;


  size_t datasize = ((omni::ptr_arith_t)pd_outb_mkr -
		     (omni::ptr_arith_t)pd_bufp_8);


  newsize = datasize + required + (size_t) omni::ALIGN_8;

  if (newsize < 1024)
    newsize += datasize;
  else
    newsize += datasize / 2;

  void* oldbufp   = pd_bufp;
  void* oldbufp_8 = pd_bufp_8;

  pd_bufp   = new char[newsize];
  pd_bufp_8 = ensure_align_8(pd_bufp);

  if (pd_clear_memory) memset(pd_bufp,0,newsize);

  if (datasize)
    memcpy(pd_bufp_8,oldbufp_8,datasize);

  pd_outb_end = (void*)((omni::ptr_arith_t)pd_bufp + newsize);
  pd_outb_mkr = (void*)((omni::ptr_arith_t)pd_bufp_8 +
			((omni::ptr_arith_t)pd_outb_mkr -
			 (omni::ptr_arith_t)oldbufp_8));
  pd_inb_mkr  = (void*)((omni::ptr_arith_t)pd_bufp_8 +
			((omni::ptr_arith_t)pd_inb_mkr -
			 (omni::ptr_arith_t)oldbufp_8));
  pd_inb_end  = (void*)((omni::ptr_arith_t)pd_bufp_8 +
			((omni::ptr_arith_t)pd_inb_end -
			 (omni::ptr_arith_t)oldbufp_8));

  if (oldbufp != pd_inline_buffer)
    delete [] (char*) oldbufp;
  return 1;
}
