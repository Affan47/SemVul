circuit_has_opened(origin_circuit_t *circ)
{
  control_event_circuit_status(circ, CIRC_EVENT_BUILT, 0);


  circ->has_opened = 1;

  switch (TO_CIRCUIT(circ)->purpose) {
    case CIRCUIT_PURPOSE_C_ESTABLISH_REND:
      rend_client_rendcirc_has_opened(circ);

      connection_ap_attach_pending();


      break;
    case CIRCUIT_PURPOSE_C_INTRODUCING:
      rend_client_introcirc_has_opened(circ);
      break;
    case CIRCUIT_PURPOSE_C_GENERAL:


      circuit_try_attaching_streams(circ);
      break;
    case CIRCUIT_PURPOSE_S_ESTABLISH_INTRO:

      rend_service_intro_has_opened(circ);
      break;
    case CIRCUIT_PURPOSE_S_CONNECT_REND:

      rend_service_rendezvous_has_opened(circ);
      break;
    case CIRCUIT_PURPOSE_TESTING:
      circuit_testing_opened(circ);
      break;


  }
}
