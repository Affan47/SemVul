Channel__WriteB0(Channel *self, const Chip* chip, Bit8u val ) {
	Bit8u fourOp = chip->reg104 & chip->opl3Active & self->fourMask;
	Bitu change;

	if ( fourOp > 0x80 )
		return;
	change = (self->chanData ^ ( val << 8 ) ) & 0x1f00;
	if ( change ) {
		self->chanData ^= change;
		Channel__UpdateFrequency( self, chip, fourOp );
	}

	if ( !(( val ^ self->regB0) & 0x20))
		return;
	self->regB0 = val;
	if ( val & 0x20 ) {
                Operator__KeyOn( Channel__Op(self, 0), 0x1 );
                Operator__KeyOn( Channel__Op(self, 1), 0x1 );
		if ( fourOp & 0x3f ) {
                        Operator__KeyOn( Channel__Op(self + 1, 0), 1 );
                        Operator__KeyOn( Channel__Op(self + 1, 1), 1 );
		}
	} else {
                Operator__KeyOff( Channel__Op(self, 0), 0x1 );
                Operator__KeyOff( Channel__Op(self, 1), 0x1 );
		if ( fourOp & 0x3f ) {
                        Operator__KeyOff( Channel__Op(self + 1, 0), 1 );
                        Operator__KeyOff( Channel__Op(self + 1, 1), 1 );
		}
	}
}
