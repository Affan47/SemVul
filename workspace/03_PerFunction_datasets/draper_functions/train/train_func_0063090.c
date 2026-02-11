generate_pass (const char *pass)
{
    struct md5_ctx md;
    char    hash[16];
    char    output[36];
    int     outsize;
    int     i;

    ASSERT (pass != 0);
    output[0] = '1';
    output[1] = ',';
    get_random_bytes (output + 2, 8);
    for (i = 0; i < 8; i++)
	output[i + 2] = alphabet[((unsigned int) output[i + 2]) % 64];
    output[10] = ',';
    md5_init_ctx (&md);
    md5_process_bytes (output + 2, 8, &md);
    md5_process_bytes (pass, strlen (pass), &md);
    md5_finish_ctx (&md, hash);
    outsize = sizeof (output) - 11;
    b64_encode (output + 11, &outsize, hash, 16);
    output[sizeof (output) - 3] = 0;
    return (STRDUP (output));
}
