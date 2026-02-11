mmc_logstats( long secs )
    {
    syslog(
    LOG_INFO, "  map cache - %d allocated, %d active (%lld bytes), %d free; hash size: %d; expire age: %ld",
    alloc_count, map_count, (int64_t) mapped_bytes, free_count, hash_size,
    expire_age );
    if ( map_count + free_count != alloc_count )
    syslog( LOG_ERR, "map counts don't add up!" );
    }
