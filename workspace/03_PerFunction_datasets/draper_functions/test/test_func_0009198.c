referrals_free (void)
{
  int walker;
  Ref_Array *grefs = NULL;

  grefs = g_get_global_referrals();

  GR_LOCK_WRITE();


  for (walker = 0; walker < grefs->ra_nextindex; walker++){
   ref_free (&grefs->ra_refs[walker]);

  }

  slapi_ch_free ((void **) &grefs->ra_refs);

  GR_UNLOCK_WRITE();

  slapi_destroy_rwlock( grefs->ra_rwlock );
}
