circuit_change_purpose(circuit_t *circ, uint8_t new_purpose)
{
  uint8_t old_purpose;

  tor_assert(!!(CIRCUIT_IS_ORIGIN(circ)) ==
             !!(CIRCUIT_PURPOSE_IS_ORIGIN(new_purpose)));

  if (circ->purpose == new_purpose) return;

  if (CIRCUIT_IS_ORIGIN(circ)) {
    char old_purpose_desc[80] = "";

    strncpy(old_purpose_desc, circuit_purpose_to_string(circ->purpose), 80-1);
    old_purpose_desc[80-1] = '\0';

    log_debug(LD_CIRC,
              "changing purpose of origin circ %d "
              "from \"%s\" (%d) to \"%s\" (%d)",
              TO_ORIGIN_CIRCUIT(circ)->global_identifier,
              old_purpose_desc,
              circ->purpose,
              circuit_purpose_to_string(new_purpose),
              new_purpose);
  }

  old_purpose = circ->purpose;
  circ->purpose = new_purpose;

  if (CIRCUIT_IS_ORIGIN(circ)) {
    control_event_circuit_purpose_changed(TO_ORIGIN_CIRCUIT(circ),
                                          old_purpose);
  }
}
