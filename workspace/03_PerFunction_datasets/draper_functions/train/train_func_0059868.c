Operator__GetSample(Operator *self, Bits modulation ) {
	Bitu vol = Operator__ForwardVolume(self);
	if ( ENV_SILENT( vol ) ) {

		self->waveIndex += self->waveCurrent;
		return 0;
	} else {
		Bitu index = Operator__ForwardWave(self);
		index += modulation;
		return Operator__GetWave( self, index, vol );
	}
}
