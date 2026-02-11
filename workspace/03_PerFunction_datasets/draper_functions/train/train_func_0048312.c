print_long(struct webauth_keyring_entry *e, size_t i)
{
    printf("       Key-Id: %lu\n", (unsigned long) i);
    printf("      Created: ");
    print_time(e->creation);
    printf("\n");
    printf("  Valid-After: ");
    print_time(e->valid_after);
    printf("\n");
    printf("     Key-Type: %d (", e->key->type);
    switch (e->key->type) {
    case WA_KEY_AES:
        printf("AES");
        break;
    default:
        printf("UNKNOWN");
        break;
    }
    printf(")\n");
    printf("   Key-Length: %d bits\n", e->key->length * 8);
    printf("  Fingerprint: ");
    print_fingerprint(e->key);
    printf("\n\n");
}
