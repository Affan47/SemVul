option_alloc (struct cmsghdr *cmsg, int datalen, int multx, int plusy)
{

  if ((multx != 1 && multx != 2 && multx != 4 && multx != 8)
      || ! (plusy >= 0 && plusy <= 7))
    return NULL;


  int dsize = cmsg->cmsg_len - CMSG_LEN (0);


  if (__builtin_expect (dsize == 0, 0))
    {
      cmsg->cmsg_len += sizeof (struct ip6_ext);
      dsize = sizeof (struct ip6_ext);
    }


  add_pad (cmsg, ((multx - (dsize & (multx - 1))) & (multx - 1)) + plusy);


  uint8_t *result = CMSG_DATA (cmsg) + cmsg->cmsg_len - CMSG_LEN (0);
  cmsg->cmsg_len += datalen;


  dsize = cmsg->cmsg_len - CMSG_LEN (0);
  add_pad (cmsg, (8 - (dsize & (8 - 1))) & (8 - 1));


  assert (((cmsg->cmsg_len - CMSG_LEN (0)) % 8) == 0);
  int len8b = (cmsg->cmsg_len - CMSG_LEN (0)) / 8 - 1;
  if (len8b >= 256)

    return NULL;

  struct ip6_ext *ie = (void *) CMSG_DATA (cmsg);
  ie->ip6e_len = len8b;

  return result;
}
