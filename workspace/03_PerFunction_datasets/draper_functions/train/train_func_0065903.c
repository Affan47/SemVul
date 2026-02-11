checkhdr (const struct hdr *hdr)
{
  enum mcheck_status status;

  if (!mcheck_used)


    return MCHECK_OK;

  switch (hdr->magic ^ ((uintptr_t) hdr->prev + (uintptr_t) hdr->next))
    {
    default:
      status = MCHECK_HEAD;
      break;
    case MAGICFREE:
      status = MCHECK_FREE;
      break;
    case MAGICWORD:
      if (((char *) &hdr[1])[hdr->size] != MAGICBYTE)
        status = MCHECK_TAIL;
      else if ((hdr->magic2 ^ (uintptr_t) hdr->block) != MAGICWORD)
        status = MCHECK_HEAD;
      else
        status = MCHECK_OK;
      break;
    }
  if (status != MCHECK_OK)
    {
      mcheck_used = 0;
      (*abortfunc) (status);
      mcheck_used = 1;
    }
  return status;
}
