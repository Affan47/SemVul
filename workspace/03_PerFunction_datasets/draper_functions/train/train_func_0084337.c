create_version_record (void)
{
  TRUSTREC rec;
  int rc;

  memset( &rec, 0, sizeof rec );
  rec.r.ver.version     = 3;
  rec.r.ver.created     = make_timestamp();
  rec.r.ver.marginals   = opt.marginals_needed;
  rec.r.ver.completes   = opt.completes_needed;
  rec.r.ver.cert_depth  = opt.max_cert_depth;
  if(opt.trust_model==TM_PGP || opt.trust_model==TM_CLASSIC)
    rec.r.ver.trust_model = opt.trust_model;
  else
    rec.r.ver.trust_model = TM_PGP;
  rec.r.ver.min_cert_level = opt.min_cert_level;
  rec.rectype = RECTYPE_VER;
  rec.recnum = 0;
  rc = tdbio_write_record( &rec );
  if( !rc )
    tdbio_sync();
  return rc;
}
