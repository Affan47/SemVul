HandleDefTimerResolution( FirstHandlerArg_DefsS * fha,
   uint32_t streamid, uint64_t ticksPerSecond )
{

   theHooks->triggerReadRecordHook( HooksC::Record_DefTimerResolution, 2,
      &streamid, &ticksPerSecond );


   fha->loc_defs.push_back( new DefRec_DefTimerResolutionS( ticksPerSecond ) );

   return OTF_RETURN_OK;
}
