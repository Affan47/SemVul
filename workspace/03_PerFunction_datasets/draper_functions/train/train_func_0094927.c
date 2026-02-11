JS_GetGCParameter(JSRuntime *rt, JSGCParamKey key)
{
    switch (key) {
      case JSGC_MAX_BYTES:
        return rt->gcMaxBytes;
      case JSGC_MAX_MALLOC_BYTES:
        return rt->gcMaxMallocBytes;
      case JSGC_STACKPOOL_LIFESPAN:
        return rt->gcEmptyArenaPoolLifespan;
      case JSGC_TRIGGER_FACTOR:
        return rt->gcTriggerFactor;
      case JSGC_BYTES:
        return rt->gcBytes;
      default:
        JS_ASSERT(key == JSGC_NUMBER);
        return rt->gcNumber;
    }
}
