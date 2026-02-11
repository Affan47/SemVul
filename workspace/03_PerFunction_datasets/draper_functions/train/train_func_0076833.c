Operator__Write80(Operator *self, const Chip* chip, Bit8u val ) {
	Bit8u change = (self->reg80 ^ val );
	Bit8u sustain;
	if ( !change )
		return;
	self->reg80 = val;
	sustain = val >> 4;

	sustain |= ( sustain + 1) & 0x10;
	self->sustainLevel = sustain << ( ENV_BITS - 5 );
	if ( change & 0x0f ) {
		Operator__UpdateRelease( self, chip );
	}
}
