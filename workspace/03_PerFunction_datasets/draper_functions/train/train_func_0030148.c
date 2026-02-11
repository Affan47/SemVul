ssh_identity_drop (gcry_sexp_t key)
{
  unsigned char key_grip[21] = { 0 };
  gpg_error_t err;

  err = ssh_key_grip (key, key_grip);
  if (err)
    goto out;

  key_grip[sizeof (key_grip) - 1] = 0;


 out:

  return err;
}
