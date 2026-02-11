__pthread_attr_setschedpolicy (attr, policy)
     pthread_attr_t *attr;
     int policy;
{
  struct pthread_attr *iattr;

  assert (sizeof (*attr) >= sizeof (struct pthread_attr));
  iattr = (struct pthread_attr *) attr;


  int ret = check_sched_policy_attr (policy);
  if (ret)
    return ret;


  iattr->schedpolicy = policy;


  iattr->flags |= ATTR_FLAG_POLICY_SET;

  return 0;
}
