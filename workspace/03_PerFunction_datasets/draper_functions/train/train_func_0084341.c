HTS_Engine_clear(HTS_Engine * engine)
{
   size_t i;

   if (engine->condition.msd_threshold != NULL)
      HTS_free(engine->condition.msd_threshold);
   if (engine->condition.duration_iw != NULL)
      HTS_free(engine->condition.duration_iw);
   if (engine->condition.gv_weight != NULL)
      HTS_free(engine->condition.gv_weight);
   if (engine->condition.parameter_iw != NULL) {
      for (i = 0; i < HTS_ModelSet_get_nstream(&engine->ms); i++)
         HTS_free(engine->condition.parameter_iw[i]);
      HTS_free(engine->condition.parameter_iw);
   }
   if (engine->condition.gv_iw != NULL) {
      for (i = 0; i < HTS_ModelSet_get_nstream(&engine->ms); i++)
         HTS_free(engine->condition.gv_iw[i]);
      HTS_free(engine->condition.gv_iw);
   }

   HTS_ModelSet_clear(&engine->ms);
   HTS_Audio_clear(&engine->audio);
   HTS_Engine_initialize(engine);
}
