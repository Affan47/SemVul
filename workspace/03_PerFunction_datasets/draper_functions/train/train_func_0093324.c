wap_push_ota_shutdown(void)
{
    gw_assert(run_status == running);
    run_status = terminating;
    gwlist_remove_producer(ota_queue);
    gwthread_join_every(main_thread);

    gwlist_destroy(ota_queue, wap_event_destroy_item);
    bearerbox_address_destroy(bearerbox);
}
