initNoRepeatedApply()
{
	outputs_ = StateOutputs(INVALID + 1, ButtonPolicy::ALL_BUTTONS);
	state_machine_ = StateMachine(INVALID + 1,
			 StateArray(int(SMI_TOTAL), ButtonPolicy::BOGUS));


	outputs_[INITIAL] = CLOSE;
	outputs_[VALID] = RESTORE | OKAY | APPLY | CANCEL;
	outputs_[INVALID] = RESTORE | CANCEL;


	state_machine_[INITIAL][SMI_READ_ONLY] = INITIAL;
	state_machine_[INITIAL][SMI_READ_WRITE] = INITIAL;
	state_machine_[INITIAL][SMI_VALID] = VALID;
	state_machine_[INITIAL][SMI_INVALID] = INVALID;

	state_machine_[VALID][SMI_VALID] = VALID;
	state_machine_[VALID][SMI_READ_ONLY] = VALID;
	state_machine_[VALID][SMI_READ_WRITE] = VALID;
	state_machine_[VALID][SMI_INVALID] = INVALID;
	state_machine_[VALID][SMI_OKAY] = INITIAL;
	state_machine_[VALID][SMI_APPLY] = INITIAL;
	state_machine_[VALID][SMI_RESTORE] = INITIAL;

	state_machine_[INVALID][SMI_INVALID] = INVALID;
	state_machine_[INVALID][SMI_READ_ONLY] = INVALID;
	state_machine_[INVALID][SMI_READ_WRITE] = INVALID;
	state_machine_[INVALID][SMI_VALID] = VALID;
	state_machine_[INVALID][SMI_RESTORE] = INITIAL;
}
