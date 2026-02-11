gstspu_execute_event (GstDVDSpu * dvdspu)
{
  switch (dvdspu->spu_input_type) {
    case SPU_INPUT_TYPE_VOBSUB:
      return gstspu_vobsub_execute_event (dvdspu);
      break;
    case SPU_INPUT_TYPE_PGS:
      return gstspu_pgs_execute_event (dvdspu);
      break;
    default:
      g_assert_not_reached ();
      break;
  }
  return FALSE;
}
