e1000_check_fiber_options(struct e1000_adapter *adapter)
{
	int bd = adapter->bd_number;
	if (num_Speed > bd) {
		e_dev_info("Speed not valid for fiber adapters, parameter "
			   "ignored\n");
	}

	if (num_Duplex > bd) {
		e_dev_info("Duplex not valid for fiber adapters, parameter "
			   "ignored\n");
	}

	if ((num_AutoNeg > bd) && (AutoNeg[bd] != 0x20)) {
		e_dev_info("AutoNeg other than 1000/Full is not valid for fiber"
			   "adapters, parameter ignored\n");
	}
}
