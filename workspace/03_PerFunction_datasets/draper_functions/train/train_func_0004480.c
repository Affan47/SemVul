update_validity (PKT_public_key *pk, PKT_user_id *uid,
                 int depth, int validity)
{
  TRUSTREC trec, vrec;
  int rc;
  ulong recno;

  namehash_from_uid(uid);

  rc = read_trust_record (pk, &trec);
  if (rc && rc != -1)
    {
      tdbio_invalid ();
      return;
    }
  if (rc == -1)
    {
      size_t dummy;

      rc = 0;
      memset (&trec, 0, sizeof trec);
      trec.recnum = tdbio_new_recnum ();
      trec.rectype = RECTYPE_TRUST;
      fingerprint_from_pk (pk, trec.r.trust.fingerprint, &dummy);
      trec.r.trust.ownertrust = 0;
      }


  recno = trec.r.trust.validlist;
  while (recno)
    {
      read_record (recno, &vrec, RECTYPE_VALID);
      if ( !memcmp (vrec.r.valid.namehash, uid->namehash, 20) )
        break;
      recno = vrec.r.valid.next;
    }

  if (!recno)
    {
      memset (&vrec, 0, sizeof vrec);
      vrec.recnum = tdbio_new_recnum ();
      vrec.rectype = RECTYPE_VALID;
      memcpy (vrec.r.valid.namehash, uid->namehash, 20);
      vrec.r.valid.next = trec.r.trust.validlist;
      trec.r.trust.validlist = vrec.recnum;
    }
  vrec.r.valid.validity = validity;
  vrec.r.valid.full_count = uid->help_full_count;
  vrec.r.valid.marginal_count = uid->help_marginal_count;
  write_record (&vrec);
  trec.r.trust.depth = depth;
  write_record (&trec);
}
