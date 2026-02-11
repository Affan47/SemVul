do_eet_sign(const char *file,
            const char *private_key,
            const char *public_key)
{
   Eet_File *ef;
   Eet_Key *key;

   ef = eet_open(file, EET_FILE_MODE_READ_WRITE);
   if (!ef)
     {
        ERR("cannot open for read+write: %s.", file);
        exit(-1);
     }

   key = eet_identity_open(public_key, private_key, NULL);
   if (!key)
     {
        ERR("cannot open key '%s:%s'.", public_key, private_key);
        exit(-1);
     }

   fprintf(stdout, "Using the following key to sign `%s`.\n", file);
   eet_identity_print(key, stdout);

   eet_identity_set(ef, key);

   eet_close(ef);
}
