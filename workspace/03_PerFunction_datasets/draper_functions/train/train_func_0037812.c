insert_hash(const char *name){
    if (!hash) return;
    GB_transaction dummy(gb_main);
    if (hash_level) {
        GBS_write_hash(hash,name,1);
        char *str = GBS_hashtab_2_string(hash);
        GBT_write_string(gb_main,hash_awar, str);
        delete str;
    }
}
