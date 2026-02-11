gen8_emit_3dstate_multisample(struct brw_context *brw, unsigned num_samples)
{
   uint32_t number_of_multisamples = 0;

   switch (num_samples) {
   case 0:
   case 1:
      number_of_multisamples = MS_NUMSAMPLES_1;
      break;
   case 2:
      number_of_multisamples = MS_NUMSAMPLES_2;
      break;
   case 4:
      number_of_multisamples = MS_NUMSAMPLES_4;
      break;
   case 8:
      number_of_multisamples = MS_NUMSAMPLES_8;
      break;
   case 16:
      number_of_multisamples = MS_NUMSAMPLES_16;
      break;
   default:
      assert(!"Unrecognized num_samples in gen8_emit_3dstate_multisample");
      break;
   }

   BEGIN_BATCH(2);
   OUT_BATCH(GEN8_3DSTATE_MULTISAMPLE << 16 | (2 - 2));
   OUT_BATCH(MS_PIXEL_LOCATION_CENTER | number_of_multisamples);
   ADVANCE_BATCH();
}
