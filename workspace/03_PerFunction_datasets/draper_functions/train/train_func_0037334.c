JS_SetGCParameter(JSRuntime *rt, JSGCParamKey key, uint32 value)
{
    switch (key) {
      case JSGC_MAX_BYTES:
        rt->gcMaxBytes = value;
        break;
      case JSGC_MAX_MALLOC_BYTES:
        rt->gcMaxMallocBytes = value;
        break;
      case JSGC_STACKPOOL_LIFESPAN:
        rt->gcEmptyArenaPoolLifespan = value;
        break;
      default:
        JS_ASSERT(key == JSGC_TRIGGER_FACTOR);
        JS_ASSERT(value >= 100);
        rt->setGCTriggerFactor(value);
        return;
    }
}
