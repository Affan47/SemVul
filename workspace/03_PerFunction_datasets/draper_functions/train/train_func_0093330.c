HandleDefFunction( FirstHandlerArg_DefsS * fha,
   uint32_t streamid, uint32_t deftoken, const char * name, uint32_t group,
   uint32_t scltoken )
{
   std::string _name(name);


   theHooks->triggerReadRecordHook( HooksC::Record_DefFunction, 5,
      &streamid, &deftoken, &_name, &group, &scltoken );


   fha->loc_defs.push_back( new DefRec_DefFunctionS
                               ( streamid, deftoken, _name, group,
                                 scltoken ) );

   return OTF_RETURN_OK;
}
