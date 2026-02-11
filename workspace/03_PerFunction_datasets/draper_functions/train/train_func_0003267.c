intel_dp_create_fake_mst_encoders(struct intel_digital_port *intel_dig_port)
{
	int i;
	struct intel_dp *intel_dp = &intel_dig_port->dp;

	for (i = PIPE_A; i <= PIPE_C; i++)
		intel_dp->mst_encoders[i] = intel_dp_create_fake_mst_encoder(intel_dig_port, i);
	return true;
}
