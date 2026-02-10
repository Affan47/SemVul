checkSparkCountInvariant (void)
{
    SparkCounters sparks = { 0, 0, 0, 0, 0, 0 };
    StgWord64 remaining = 0;
    nat i;

    for (i = 0; i < n_capabilities; i++) {
        sparks.created   += capabilities[i].spark_stats.created;
        sparks.dud       += capabilities[i].spark_stats.dud;
        sparks.overflowed+= capabilities[i].spark_stats.overflowed;
        sparks.converted += capabilities[i].spark_stats.converted;
        sparks.gcd       += capabilities[i].spark_stats.gcd;
        sparks.fizzled   += capabilities[i].spark_stats.fizzled;
        remaining        += sparkPoolSize(capabilities[i].sparks);
    }


    debugTrace(DEBUG_sparks,"spark invariant: %ld == %ld + %ld + %ld + %ld "
                            "(created == converted + remaining + gcd + fizzled)",
                            sparks.created, sparks.converted, remaining,
                            sparks.gcd, sparks.fizzled);

    return (sparks.created ==
              sparks.converted + remaining + sparks.gcd + sparks.fizzled);

}
