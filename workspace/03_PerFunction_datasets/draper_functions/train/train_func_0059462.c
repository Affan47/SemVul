OnSignal (SignalId Signal, G_GNUC_UNUSED Object *Child)
{
	if (Signal == OnChangedSignal && !HasChildren ())
		delete this;
	return true;
}
