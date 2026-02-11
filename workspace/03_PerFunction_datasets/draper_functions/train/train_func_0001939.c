forceCommandPropagation(redisClient *c, int flags) {
    if (flags & REDIS_PROPAGATE_REPL) c->flags |= REDIS_FORCE_REPL;
    if (flags & REDIS_PROPAGATE_AOF) c->flags |= REDIS_FORCE_AOF;
}
