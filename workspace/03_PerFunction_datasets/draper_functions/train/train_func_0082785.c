ID_to_class(context_type *context, unsigned short ID)
{
    hash_table_type *class_hash = &(context->class_hash);
    hash_bucket_type *bucket = GET_BUCKET(class_hash, ID);
    if (bucket->class == 0) {
        assert(bucket->loadable == JNI_TRUE);
        bucket->class = load_class_global(context, bucket->name);
    }
    return bucket->class;
}
