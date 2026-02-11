emit_bucket(struct ntb_main_context_bucket *bucket)
{
        struct ntb_main_context_source *source, *tmp_source;
        ntb_main_context_timer_callback callback;

        ntb_list_for_each_safe(source,
                               tmp_source,
                               &bucket->sources,
                               link) {
                callback = source->callback;
                callback(source, source->user_data);
        }

        bucket->minutes_passed = 0;
}
