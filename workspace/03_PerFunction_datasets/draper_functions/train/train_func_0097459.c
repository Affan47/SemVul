encryptInPlace(ThreefishKey_t* key,
                    const uint64_t* chain,
                    uint64_t* plain_text,
                    const uint64_t num_blocks)
{
    pd2("encryptInPlace(key:%lu, chain:%lu, plain_text:%lu, num_blocks:%lu)\n", key->key[0], chain[0], plain_text[0], num_blocks);
    switch(key->stateSize)
    {
        case 256: cbc256Encrypt(key, chain, plain_text, num_blocks);
        break;
        case 512: cbc512Encrypt(key, chain, plain_text, num_blocks);
        break;
        case 1024: cbc1024Encrypt(key, chain, plain_text, num_blocks);
        break;
        default:
        {
            perror("Invalid state size cannot continue\n");
            exit(9);
        }
        break;
    }
}
