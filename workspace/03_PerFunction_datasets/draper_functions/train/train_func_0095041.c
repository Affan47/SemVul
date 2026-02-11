nssCertificateStore_RemoveCertLOCKED (
  nssCertificateStore *store,
  NSSCertificate *cert
)
{
    certificate_hash_entry *entry;
    entry = (certificate_hash_entry *)
                              nssHash_Lookup(store->issuer_and_serial, cert);
    if (entry && entry->cert == cert) {
	remove_certificate_entry(store, cert);
	remove_subject_entry(store, cert);
    }
}
