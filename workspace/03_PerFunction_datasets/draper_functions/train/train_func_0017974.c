lookup_string_ctor_signature (MonoMethodSignature *sig)
{
	MonoMethodSignature *callsig;
	CtorSigPair *cs;
	GSList *item;

	mono_marshal_lock ();
	callsig = NULL;
	for (item = strsig_list; item; item = item->next) {
		cs = (CtorSigPair *)item->data;


		if (mono_metadata_signature_equal (sig, cs->ctor_sig)) {
			callsig = cs->sig;
			break;
		}
	}
	mono_marshal_unlock ();
	return callsig;
}
