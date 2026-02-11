Channel__WriteC0(Channel *self, const Chip* chip, Bit8u val ) {
	Bit8u change = val ^ self->regC0;
	if ( !change )
		return;
	self->regC0 = val;
	self->feedback = ( val >> 1 ) & 7;
	if ( self->feedback ) {

		self->feedback = 9 - self->feedback;
	} else {
		self->feedback = 31;
	}

	if ( chip->opl3Active ) {

		if ( (chip->reg104 & self->fourMask) & 0x3f ) {
			Channel* chan0, *chan1;
			Bit8u synth;

			if ( !(self->fourMask & 0x80 ) ) {
				chan0 = self;
				chan1 = self + 1;
			} else {
				chan0 = self - 1;
				chan1 = self;
			}

			synth = ( (chan0->regC0 & 1) << 0 )| (( chan1->regC0 & 1) << 1 );
			switch ( synth ) {
			case 0:
				chan0->synthHandler = Channel__BlockTemplate_sm3FMFM;
				break;
			case 1:
				chan0->synthHandler = Channel__BlockTemplate_sm3AMFM;
				break;
			case 2:
				chan0->synthHandler = Channel__BlockTemplate_sm3FMAM ;
				break;
			case 3:
				chan0->synthHandler = Channel__BlockTemplate_sm3AMAM ;
				break;
			}

		} else if ((self->fourMask & 0x40) && ( chip->regBD & 0x20) ) {


		} else if ( val & 1 ) {
			self->synthHandler = Channel__BlockTemplate_sm3AM;
		} else {
			self->synthHandler = Channel__BlockTemplate_sm3FM;
		}
		self->maskLeft = ( val & 0x10 ) ? -1 : 0;
		self->maskRight = ( val & 0x20 ) ? -1 : 0;

	} else {

		if ( (self->fourMask & 0x40) && ( chip->regBD & 0x20 ) ) {


		} else if ( val & 1 ) {
			self->synthHandler = Channel__BlockTemplate_sm2AM;
		} else {
			self->synthHandler = Channel__BlockTemplate_sm2FM;
		}
	}
}
