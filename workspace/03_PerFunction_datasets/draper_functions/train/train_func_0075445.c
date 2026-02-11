enumerate_assertion_exists_in_slot (GPkcs11Slot              *slot,
                                    GTlsInteraction          *interaction,
                                    GPkcs11Array             *match,
                                    GPkcs11Accumulator        accumulator,
                                    gpointer                  user_data,
                                    GCancellable             *cancellable,
                                    GError                  **error)
{
  GPkcs11EnumerateState state;

  state = g_pkcs11_slot_enumerate (slot, interaction, match->attrs, match->count,
                                   FALSE, NULL, 0, accumulate_stop, NULL,
                                   cancellable, error);


  if (state == G_PKCS11_ENUMERATE_STOP)
    return enumerate_call_accumulator (accumulator, NULL, user_data);

  return state;
}
